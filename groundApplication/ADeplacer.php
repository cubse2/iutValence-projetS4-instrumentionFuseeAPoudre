<?php

//TODO A déplacer dans le fichier php traitant le formulaire d'envoi de fichier
function loadFile(){

        if ($_FILES['file']['error'] != 0) {
            return "Une erreur c'est produite durant le transfert";
        }
        if(!move_uploaded_file($_FILES['file']['tmp_name'], "tmp/".FILE_FLIGHT_DATA)){
            return "Une erreur s'est produite durant la copie du fichier";
        }
        return TRUE;
}

function exportToCsv($flightDataArray){
    
    $file = fopen(EXPORTED_FILE, 'w');
    foreach ($flightDataArray as $flightData){
        fputcsv($file, $flightData);
    }
    fclose($file);
}