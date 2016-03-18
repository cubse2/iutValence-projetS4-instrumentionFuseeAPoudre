<?php

class postFlightMonitor {
    
    public $flightDataStorage;
    
    public function __construct($flightDataStorage) {
        $this->flightDataStorage = $flightDataStorage;
        if(empty($this->flightDataStorage->timeStampedFlightDataSampleTable)){
            $this->flightDataStorage->readFromFile();
        }
    }
    
    public function createTimeTable(){
        $timeTable = array();
        foreach ($this->flightDataStorage->timeStampedFlightDataSampleTable as $flightDataSample){
            $timeTable[] = $flightDataSample->getTimestamp();
        }
        return $timeTable;
    }
    
    public function createYAccelerationTable(){
        $yAcceleration = array();
        foreach($this->flightDataStorage->timeStampedFlightDataSampleTable as $flightDataSample){
            $yAcceleration[] =  $flightDataSample->getAccelerationY();
        }
        return $yAcceleration;
    }
    
    public function createYVelocityTable(){
        $yVelocity = array();
        $prevYVelocityValue = 0;
        $prevTimeValue = 0;
        foreach($this->flightDataStorage->timeStampedFlightDataSampleTable as $flightDataSample){
            $newYVelocity = $prevYVelocityValue + $flightDataSample->getAccelerationY() * ($flightDataSample->getTimestamp() - $prevTimeValue);
            $yVelocity[] = $newYVelocity;
            $prevYVelocityValue = $newYVelocity;
            $prevTimeValue = $flightDataSample->getTimestamp();
            
        }
        return $yVelocity;
    }
    
    public function createAltitudeTable(){
        $altitude = array();
        foreach($this->flightDataStorage->timeStampedFlightDataSampleTable as $flightDataSample){
            //$altitudeAndTime['altitude'][] =  44330*(bcpow(1-($flightDataSample->getPressure()/1013.25),(1/5.255),3));
            $altitude[] =  $flightDataSample->getPressure();
        }
        return $altitude;
    }
    
    public function createXVelocityTable(){
        $xVelocity = array();
        $prevXVelocityValue = 0;
        $prevTimeValue = 0;
        foreach($this->flightDataStorage->timeStampedFlightDataSampleTable as $flightDataSample){
            $newXVelocity = $prevXVelocityValue + $flightDataSample->getAccelerationX() * ($flightDataSample->getTimestamp() - $prevTimeValue);
            $xVelocity[] = $newXVelocity;
            $prevXVelocityValue = $newXVelocity;
            $prevTimeValue = $flightDataSample->getTimestamp();
            
        }
        return $xVelocity;
    }
    
    public function createZVelocityTable(){
        $zVelocity = array();
        $prevXVelocityValue = 0;
        $prevTimeValue = 0;
        foreach($this->flightDataStorage->timeStampedFlightDataSampleTable as $flightDataSample){
            $newZVelocity = $prevZVelocityValue + $flightDataSample->getAccelerationZ() * ($flightDataSample->getTimestamp() - $prevTimeValue);
            $zVelocity[] = $newZVelocity;
            $prevZVelocityValue = $newZVelocity;
            $prevTimeValue = $flightDataSample->getTimestamp();
            
        }
        return $zVelocity;
    }
    
    public function createXPosition(){
        $xPosition = array();
        $time = $this->createTimeTable();
        $xVelocity = $this->createYVelocityTable();
        $prevXPositionValue = 0;
        $prevTimeValue = 0;
        for ($i = 0; $i < count($xVelocity); $i++){
            $newXPosition = $prevXPositionValue + $xVelocity[$i] * ($time[$i] - $prevTimeValue);
            $xPosition[] = $newXPosition;
            $prevXPositionValue = $newXPosition;
            $prevTimeValue = $time[$i];
        }
        return $xPosition;
    }
    
    public function createYPosition(){
        $yPosition = array();
        $time = $this->createTimeTable();
        $yVelocity = $this->createYVelocityTable();
        $prevYPositionValue = 0;
        $prevTimeValue = 0;
        for ($i = 0; $i < count($yVelocity); $i++){
            $newYPosition = $prevYPositionValue + $yVelocity[$i] * ($time[$i] - $prevTimeValue);
            $yPosition[] = $newYPosition;
            $prevYPositionValue = $newYPosition;
            $prevTimeValue = $time[$i];
        }
        return $yPosition;
    }
    
    public function createZPosition(){
        $zPosition = array();
        $time = $this->createTimeTable();
        $zVelocity = $this->createYVelocityTable();
        $prevZPositionValue = 0;
        $prevTimeValue = 0;
        for ($i = 0; $i < count($zVelocity); $i++){
            $newZPosition = $prevZPositionValue + $zVelocity[$i] * ($time[$i] - $prevTimeValue);
            $zPosition[] = $newZPosition;
            $prevZPositionValue = $newZPosition;
            $prevTimeValue = $time[$i];
        }
        return $zPosition;
    }
    
    public function createPosition(){
        $xPosition = $this->createXPosition();
        $yPosition = $this->createYPosition();
        $zPosition = $this->createZPosition();
        $path3D = array(
            'x' => $xPosition,
            'y' => $yPosition,
            'z' => $zPosition
        );
        return $path3D;
    }
}
