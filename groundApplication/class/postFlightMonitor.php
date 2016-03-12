<?php

class postFlightMonitor {
    
    public $flightDataStorage;
    
    public function __construct($flightDataStorage) {
        $this->flightDataStorage = $flightDataStorage;
        if(empty($this->flightDataStorage->timeStampedFlightDataSampleTable)){
            $this->flightDataStorage->readFromFile();
        }
    }
    
    public function createYAccelerationAndTimeTable(){
        $AccelerationYAndTime = array();
        foreach($this->flightDataStorage->timeStampedFlightDataSampleTable as $flightDataSample){
            $AccelerationYAndTime['time'][] =  $flightDataSample->getTimestamp();
            $AccelerationYAndTime['accelerationY'][] =  $flightDataSample->getAccelerationY();
        }
        return $AccelerationYAndTime;
    }
    
    public function createVelocityYAndTimeTable(){
        $velocityYAndTime = array();
        $prevVelocityYValue = 0;
        $prevTimeValue = 0;
        foreach($this->flightDataStorage->timeStampedFlightDataSampleTable as $flightDataSample){
            $velocityYAndTime['time'][] =  $flightDataSample->getTimestamp();
            $newVelocityY = $prevVelocityYValue + $flightDataSample->getAccelerationY() * ($flightDataSample->getTimestamp() - $prevTimeValue);
            $velocityYAndTime['velocityY'][] = $newVelocityY;
            $prevVelocityYValue = $newVelocityY;
            $prevTimeValue = $flightDataSample->getTimestamp();
            
        }
        return $velocityYAndTime;
    }
    
    public function createAltitudeAndTimeTable(){
        $altitudeAndTime = array();
        foreach($this->flightDataStorage->timeStampedFlightDataSampleTable as $flightDataSample){
            $altitudeAndTime['time'][] =  $flightDataSample->getTimestamp();
            //$altitudeAndTime['altitude'][] =  44330*(bcpow(1-($flightDataSample->getPressure()/1013.25),(1/5.255),3));
            $altitudeAndTime['altitude'][] =  $flightDataSample->getPressure();
        }
        return $altitudeAndTime;
    }
    
    public function createVelocityXAndTimeTable(){
        $velocityXAndTime = array();
        $prevVelocityXValue = 0;
        $prevTimeValue = 0;
        foreach($this->flightDataStorage->timeStampedFlightDataSampleTable as $flightDataSample){
            $newVelocityX = $prevVelocityXValue + $flightDataSample->getAccelerationX() * ($flightDataSample->getTimestamp() - $prevTimeValue);
            $velocityXAndTime['time'][] = $flightDataSample->getTimestamp();
            $velocityXAndTime['velocityX'][] = $newVelocityX;
            $prevVelocityXValue = $newVelocityX;
            $prevTimeValue = $flightDataSample->getTimestamp();
            
        }
        return $velocityXAndTime;
    }
    
    public function createVelocityZAndTimeTable(){
        $velocityZAndTime = array();
        $prevVelocityZValue = 0;
        $prevTimeValue = 0;
        foreach($this->flightDataStorage->timeStampedFlightDataSampleTable as $flightDataSample){
            $newVelocityZ = $prevVelocityZValue + $flightDataSample->getAccelerationZ() * ($flightDataSample->getTimestamp() - $prevTimeValue);
            $velocityZAndTime['time'][] = $flightDataSample->getTimestamp();
            $velocityZAndTime['velocityZ'][] = $newVelocityZ;
            $prevVelocityZValue = $newVelocityZ;
            $prevTimeValue = $flightDataSample->getTimestamp();
            
        }
        return $velocityZAndTime;
    }
    
    public function createPositionXAndTimeTable(){
        $positionXAndTime = array();
        $velocityXAndTime = $this->createVelocityXAndTimeTable();
        $prevPositionXValue = 0;
        $prevTimeValue = 0;
        for ($i = 0; $i < count($velocityXAndTime['time']); $i++){
            $newPositionX = $prevPositionXValue + $velocityXAndTime['velocityX'][$i] * ($velocityXAndTime['time'][$i] - $prevTimeValue);
            $positionXAndTime['time'][] = $velocityXAndTime['time'][$i];
            $positionXAndTime['positionX'][] = $newPositionX;
            $prevPositionXValue = $newPositionX;
            $prevTimeValue = $velocityXAndTime['time'][$i];
        }
        return $positionXAndTime;
    }
    
    public function createPositionYAndTimeTable(){
        $positionYAndTime = array();
        $velocityYAndTime = $this->createVelocityYAndTimeTable();
        $prevPositionYValue = 0;
        $prevTimeValue = 0;
        for ($i = 0; $i < count($velocityYAndTime['time']); $i++){
            $newPositionY = $prevPositionYValue + $velocityYAndTime['velocityY'][$i] * ($velocityYAndTime['time'][$i] - $prevTimeValue);
            $positionYAndTime['time'][] = $velocityYAndTime['time'][$i];
            $positionYAndTime['positionY'][] = $newPositionY;
            $prevPositionYValue = $newPositionY;
            $prevTimeValue = $velocityYAndTime['time'][$i];
        }
        return $positionYAndTime;
    }
    
    public function createPositionZAndTimeTable(){
        $positionZAndTime = array();
        $velocityZAndTime = $this->createVelocityZAndTimeTable();
        $prevPositionZValue = 0;
        $prevTimeValue = 0;
        for ($i = 0; $i < count($velocityZAndTime['time']); $i++){
            $newPositionZ = $prevPositionZValue + $velocityZAndTime['velocityZ'][$i] * ($velocityZAndTime['time'][$i] - $prevTimeValue);
            $positionZAndTime['time'][] = $velocityZAndTime['time'][$i];
            $positionZAndTime['positionZ'][] = $newPositionZ;
            $prevPositionZValue = $newPositionZ;
            $prevTimeValue = $velocityZAndTime['time'][$i];
        }
        return $positionZAndTime;
    }
    
    public function createPosition(){
        $positionX = $this->createPositionXAndTimeTable();
        $positionY = $this->createPositionYAndTimeTable();
        $positionZ = $this->createPositionZAndTimeTable();
        $path3D = array(
            'time' => $positionX['time'],
            'x' => $positionX['positionX'],
            'y' => $positionY['positionY'],
            'z' => $positionZ['positionZ']
        );
        return $path3D;
    }
}
