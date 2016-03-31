<?php

class TimeStampedFileFlightDataStorage implements FlightDataStorage{

    public $timeStampedFlightDataSampleTable = array();

    private $timeStampedFileFlightDataReader;

    public function __construct($timeStampedFileFlightDataReader){

        $this->timeStampedFileFlightDataReader = $timeStampedFileFlightDataReader;
    }

    public function readFromFile(){

        while ($data = $this->timeStampedFileFlightDataReader->readTimeStampedFlightData()){
            $this->timeStampedFlightDataSampleTable[] = $data;
        }
    }

    public function iterator(){


    }
}