<?php

class postFlightMonitor {
    
    public $flightDataStorage;
    
    public function __construct($flightDataStorage) {
        $this->flightDataStorage = $flightDataStorage;
    }
    
    private function createYAccelerationAndTimeTable(){
        $AccelerationYAndTime = array();
        foreach($this->flightDataStorage->timeStampedFlightDataSampleTable as $flightDataSample){
            $AccelerationYAndTime['time'][] =  $flightDataSample->getTimestamp();
            $AccelerationYAndTime['AccelerationY'][] =  $flightDataSample->getAccelerationY();
        }
        return $YAccelerationAndTime;
    }
    
    private function createVelocityYAndTimeTable(){
        $gyroscopeYAndTime = array();
        foreach($this->flightDataStorage->timeStampedFlightDataSampleTable as $flightDataSample){
            $gyroscopeYAndTime['time'][] =  $flightDataSample->getTimestamp();
            $gyroscopeYAndTime['gyroscopeY'][] =  $flightDataSample->getGyroscopeY();
        }
        return $gyroscopeYAndTime;
    }
    
    private function createAltitudeAndTimeTable(){
        $altitudeAndTime = array();
        foreach($this->flightDataStorage->timeStampedFlightDataSampleTable as $flightDataSample){
            $gyroscopeYAndTime['time'][] =  $flightDataSample->getTimestamp();
            $gyroscopeYAndTime['altitude'][] =  44330*(bcpow(1-($flightDataSample->getGyroscopeY()/1013.25),(1/5.255)));
        }
        return $gyroscopeYAndTime;
    }
}
