<?php

class TimeStampedFlightDataSample extends FlightDataSample{

    private $timestamp;

    public function __construct($accelerationX, $accelerationY, $accelerationZ, $gyroscopeX, $gyroscopeY, $gyroscopeZ, $magnetismX, $magnetismY, $magnetismZ, $pressure, $timestamp){

        parent::__construct($accelerationX, $accelerationY, $accelerationZ, $gyroscopeX, $gyroscopeY, $gyroscopeZ, $magnetismX, $magnetismY, $magnetismZ, $pressure);
        $this->timestamp = $timestamp;
    }

    public function getTimestamp(){
        return $this->timestamp;
    }
}