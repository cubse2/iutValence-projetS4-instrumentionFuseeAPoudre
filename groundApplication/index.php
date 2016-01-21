<?php

    require_once 'config/config.php';

    function __autoload($class) {
        require_once "class/$class.php";
    }

    $timeStampedFileFlightDataStorage = new TimeStampedFileFlightDataStorage(new TimeStampedFileFlightDataReader());

    $timeStampedFileFlightDataStorage->readFromFile();

    echo "<pre>";
    var_dump($timeStampedFileFlightDataStorage->timeStampedFlightDataSampleTable);
    echo "</pre>";