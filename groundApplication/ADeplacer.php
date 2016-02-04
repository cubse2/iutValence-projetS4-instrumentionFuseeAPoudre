<?php

function exportToCsv($flightDataArray){
    
    $file = fopen(EXPORTED_FILE, 'w');
    foreach ($flightDataArray as $flightData){
        fputcsv($file, $flightData);
    }
    fclose($file);
}