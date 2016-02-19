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
            $velocityYAndTime['velocityY'][] =  $prevVelocityYValue + $flightDataSample->getAccelerationY() * ($flightDataSample->getTimestamp() - $prevTimeValue);
        }
        return $velocityYAndTime;
    }
    
    public function createAltitudeAndTimeTable(){
        $altitudeAndTime = array();
        foreach($this->flightDataStorage->timeStampedFlightDataSampleTable as $flightDataSample){
            $altitudeAndTime['time'][] =  $flightDataSample->getTimestamp();
            $altitudeAndTime['altitude'][] =  44330*(bcpow(1-($flightDataSample->getPressure()/1013.25),(1/5.255),3));
        }
        return $altitudeAndTime;
    }
}
