<?php

class TimeStampedFlightDataSample extends FlightDataSample{

    private $timestamp;

    public function __construct($timestamp, $accelerationX, $accelerationY, $accelerationZ, $gyroscopeX, $gyroscopeY, $gyroscopeZ, $magnetismX, $magnetismY, $magnetismZ, $pressure){

        parent::__construct($accelerationX, $accelerationY, $accelerationZ, $gyroscopeX, $gyroscopeY, $gyroscopeZ, $magnetismX, $magnetismY, $magnetismZ, $pressure);
        $this->timestamp = $timestamp;
    }

    public function getTimestamp(){
        return $this->timestamp;
    }

    public function getTimestampInSecond(){
        return $this->timestamp/1000;
    }
}