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
        $timeStampStart = $this->flightDataStorage->timeStampedFlightDataSampleTable[0]->getTimestampInSecond();
        foreach ($this->flightDataStorage->timeStampedFlightDataSampleTable as $flightDataSample){
            $timeTable[] = $flightDataSample->getTimestampInSecond()-$timeStampStart;
        }
        return $timeTable;
    }
    
    public function createZAccelerationTable(){
        $zAcceleration = array();
        foreach($this->flightDataStorage->timeStampedFlightDataSampleTable as $flightDataSample){
            $zAcceleration[] =  $flightDataSample->getAccelerationZ();
        }
        return $zAcceleration;
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
        $prevXAccelerationValue = 0;
        $prevXVelocityValue = 0;
        $prevTimeValue = 0;
        foreach($this->flightDataStorage->timeStampedFlightDataSampleTable as $flightDataSample){
            $newXVelocity = ($prevXAccelerationValue + (($flightDataSample->getAccelerationX() - $prevXAccelerationValue)/2) * ($flightDataSample->getTimestampInSecond() - $prevTimeValue)) + $prevXVelocityValue;
            $xVelocity[] = $newXVelocity;
            $prevXAccelerationValue = $flightDataSample->getAccelerationX();
            $prevXVelocityValue = $newXVelocity;
            $prevTimeValue = $flightDataSample->getTimestampInSecond();
            
        }
        return $xVelocity;
    }

    public function createYVelocityTable(){
        $yVelocity = array();
        $prevYAccelerationValue = 0;
        $prevYVelocityValue = 0;
        $prevTimeValue = 0;
        foreach($this->flightDataStorage->timeStampedFlightDataSampleTable as $flightDataSample){
            $newYVelocity = ($prevYAccelerationValue + (($flightDataSample->getAccelerationY() - $prevYAccelerationValue)/2) * ($flightDataSample->getTimestampInSecond() - $prevTimeValue)) + $prevYVelocityValue;
            $yVelocity[] = $newYVelocity;
            $prevYAccelerationValue = $flightDataSample->getAccelerationY();
            $prevYVelocityValue = $newYVelocity;
            $prevTimeValue = $flightDataSample->getTimestampInSecond();
            
        }
        return $yVelocity;
    }
    
    public function createZVelocityTable(){
        $zVelocity = array();
        $prevZAccelerationValue = 0;
        $prevZVelocityValue = 0;
        $prevTimeValue = 0;
        foreach($this->flightDataStorage->timeStampedFlightDataSampleTable as $flightDataSample){
            $newZVelocity = ($prevZAccelerationValue + (($flightDataSample->getAccelerationZ() - $prevZAccelerationValue)/2) * ($flightDataSample->getTimestampInSecond() - $prevTimeValue)) - 9.81 + $prevZVelocityValue;
            $zVelocity[] = $newZVelocity;
            $prevZAccelerationValue = $flightDataSample->getAccelerationZ();
            $prevZVelocityValue = $newZVelocity;
            $prevTimeValue = $flightDataSample->getTimestampInSecond();
            
        }
        return $zVelocity;
    }
    
    public function createXPosition(){
        $xPosition = array();
        $time = $this->createTimeTable();
        $xVelocity = $this->createYVelocityTable();
        $prevXVelocityValue = 0;
        $prevXPositionValue = 0;
        $prevTimeValue = 0;
        for ($i = 0; $i < count($xVelocity); $i++){
            $newXPosition = ($prevXVelocityValue + (($xVelocity[$i] - $prevXVelocityValue)/2) * ($time[$i] - $prevTimeValue)) + $prevXPositionValue;
            $xPosition[] = $newXPosition;
            $prevXVelocityValue = $xVelocity[$i];
            $prevXPositionValue = $newXPosition;
            $prevTimeValue = $time[$i];
        }
        return $xPosition;
    }
    
    public function createYPosition(){
        $yPosition = array();
        $time = $this->createTimeTable();
        $yVelocity = $this->createYVelocityTable();
        $prevYVelocityValue = 0;
        $prevYPositionValue = 0;
        $prevTimeValue = 0;
        for ($i = 0; $i < count($yVelocity); $i++){
            $newYPosition = ($prevYVelocityValue + (($yVelocity[$i] - $prevYVelocityValue)/2) * ($time[$i] - $prevTimeValue)) + $prevYPositionValue;
            $yPosition[] = $newYPosition;
            $prevXVelocityValue = $yVelocity[$i];
            $prevYPositionValue = $newYPosition;
            $prevTimeValue = $time[$i];
        }
        return $yPosition;
    }
    
    public function createZPosition(){
        $zPosition = array();
        $time = $this->createTimeTable();
        $zVelocity = $this->createZVelocityTable();
        $prevZVelocityValue = 0;
        $prevZPositionValue = 0;
        $prevTimeValue = 0;
        for ($i = 0; $i < count($zVelocity); $i++){
            $newZPosition = ($prevZVelocityValue + (($zVelocity[$i] - $prevZVelocityValue)/2) * ($time[$i] - $prevTimeValue)) + $prevZPositionValue;
            $zPosition[] = $newZPosition;
            $prevZVelocityValue = $zVelocity[$i];
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
