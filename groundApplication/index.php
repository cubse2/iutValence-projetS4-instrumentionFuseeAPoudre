<?php

require_once 'config/config.php';

    function __autoload($class) {
        require_once "class/$class.php";
    }

    //$timeStampedFileFlightDataStorage = new TimeStampedFileFlightDataStorage(new TimeStampedFileFlightDataReader());

    //$timeStampedFileFlightDataStorage->readFromFile();

    //echo "<pre>";
    //var_dump($timeStampedFileFlightDataStorage->timeStampedFlightDataSampleTable);
    //echo "</pre>";

?>
<!DOCTYPE html>
<html lang="fr-FR">
    <head>
        <title>Menu</title>
        <meta name="description" content="Extrait les donnéesdu fichier généré par l'application embarqué">
        <meta charset="UTF-8">
        <meta name="author" content="Baptiste Thevenet">
        <link rel="stylesheet" type="text/css" href="skeleton.css">
        <link rel="stylesheet" type="text/css" href="knacss.css">
        <link rel="stylesheet" type="text/css" href="my_style.css">
        <script src="//code.jquery.com/jquery-1.12.0.min.js"></script>
    </head>
    <body>
        <div class="main small-w100">
            <h1>Menu</h1>
            <form action="" method="post">
                <a href="chargement_donnees.php" class="button w100">Visualiser des données existantes</a>
                <a href="#" class="button w100">Visualiser des données en temps réel</a>
            </form>
        </div>
    </body>
</html>
<script src="myScript.js"></script>

