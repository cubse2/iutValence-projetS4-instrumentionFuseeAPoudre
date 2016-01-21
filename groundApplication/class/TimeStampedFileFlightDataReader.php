<?php


class TimeStampedFileFlightDataReader implements FlightDataReader{

    private $file = array();

    private $currentRow;

    private $rowCount;

    public function __construct(){

        $this->currentRow = 0;
        $this->rowCount = 0;
        $openFile = fopen(FILE_FLIGHT_DATA, 'r');
        while ($data = fgetcsv($openFile, 0, ';')) {
            $this->file[] = $data;
            $this->rowCount++;
        }
        fclose($openFile);
    }

    public function readTimeStampedFlightData(){

        if ($this->currentRow < $this->rowCount){
            $data = $this->file[$this->currentRow];
            $this->currentRow++;
            return new TimeStampedFlightDataSample($data[0], $data[1], $data[2], $data[3], $data[4], $data[5], $data[6], $data[7], $data[8], $data[9], $data[10]);
        }
        return FALSE;
    }
}