<?php

class FlightDataSample{

    private $accelerationX;
    private $accelerationY;
    private $accelerationZ;
    private $gyroscopeX;
    private $gyroscopeY;
    private $gyroscopeZ;
    private $magnetismX;
    private $magnetismY;
    private $magnetismZ;
    private $pressure;

    /**
     * FlightDataSample constructor.
     * @param $accelerationX
     * @param $accelerationY
     * @param $accelerationZ
     * @param $gyroscopeX
     * @param $gyroscopeY
     * @param $gyroscopeZ
     * @param $magnetismX
     * @param $magnetismY
     * @param $magnetismZ
     * @param $pressure
     */
    public function __construct($accelerationX, $accelerationY, $accelerationZ, $gyroscopeX, $gyroscopeY, $gyroscopeZ, $magnetismX, $magnetismY, $magnetismZ, $pressure){
        $this->accelerationX = $accelerationX;
        $this->accelerationY = $accelerationY;
        $this->accelerationZ = $accelerationZ;
        $this->gyroscopeX = $gyroscopeX;
        $this->gyroscopeY = $gyroscopeY;
        $this->gyroscopeZ = $gyroscopeZ;
        $this->magnetismX = $magnetismX;
        $this->magnetismY = $magnetismY;
        $this->magnetismZ = $magnetismZ;
        $this->pressure = $pressure;
    }


    public function getAccelerationX(){
        return $this->accelerationX;
    }

    public function getAccelerationY(){
        return $this->accelerationY;
    }

    public function getAccelerationZ(){
        return $this->accelerationZ;
    }

    public function getGyroscopeX(){
        return $this->gyroscopeX;
    }

    public function getGyroscopeY(){
        return $this->gyroscopeY;
    }

    public function getGyroscopeZ(){
        return $this->gyroscopeZ;
    }

    public function getMagnetismX(){
        return $this->magnetismX;
    }

    public function getMagnetismY(){
        return $this->magnetismY;
    }

    public function getMagnetismZ(){
        return $this->magnetismZ;
    }

    public function getPressure(){
        return $this->pressure;
    }
}