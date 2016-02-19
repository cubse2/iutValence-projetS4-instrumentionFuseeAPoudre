<?php

require_once 'config/config.php';

function __autoload($class){
    require_once "class/$class.php";
}

function exportToCsv($flightDataArray){
    
    $file = fopen(EXPORTED_FILE, 'w');
    foreach ($flightDataArray as $flightData){
        fputcsv($file, $flightData);
    }
    fclose($file);
}

$postFlightMonitor = new postFlightMonitor(new TimeStampedFileFlightDataStorage(new TimeStampedFileFlightDataReader()));

$acceleration = $postFlightMonitor->createYAccelerationAndTimeTable();
$accelerationLabels = implode(',',$acceleration['time']);
$accelerationValues = implode(',',$acceleration['accelerationY']);

$altitude = $postFlightMonitor->createAltitudeAndTimeTable();
$altitudeLabels = implode(',',$altitude['time']);
$altitudeValues = implode(',',$altitude['altitude']);

$velocity = $postFlightMonitor->createVelocityYAndTimeTable();
$velocityLabels = implode(',',$velocity['time']);
$velocityValues = implode(',',$velocity['velocityY']);
?>
<!DOCTYPE html>
<html lang="fr-FR">
    <head>
        <title>Visualiser les données post-vol</title>
        <meta name="description" content="">
        <meta charset="UTF-8">
        <meta name="author" content="Baptiste Thevenet">
        <link rel="stylesheet" type="text/css" href="skeleton.css">
        <link rel="stylesheet" type="text/css" href="knacss.css">
        <link rel="stylesheet" type="text/css" href="my_style.css">
        <script src="//code.jquery.com/jquery-1.12.0.min.js"></script>
        <script src="js/Chart.min.js"></script>
    </head>
    <body>
        <canvas style="background: white" id="acceleration" width="1200" height="600"></canvas>
        <canvas style="background: white" id="altitude" width="1200" height="600"></canvas>
        <canvas style="background: white" id="velocity" width="1200" height="600"></canvas>
    </body>
</html>
<script>
    var data = {
        labels: [<?php echo $accelerationLabels ?>],
        datasets: [
            {
                label: "Accélération",
                fillColor: "rgba(220,220,220,0.2)",
                strokeColor: "rgba(220,220,220,1)",
                pointColor: "rgba(220,220,220,1)",
                pointStrokeColor: "#fff",
                pointHighlightFill: "#fff",
                pointHighlightStroke: "rgba(220,220,220,1)",
                data: [<?php echo $accelerationValues ?>]
            }
        ]
    };
    var ctx = document.getElementById("acceleration").getContext("2d");
    var myNewChart = new Chart(ctx).Line(data);
    
    var data = {
        labels: [<?php echo $altitudeLabels ?>],
        datasets: [
            {
                label: "Altitude",
                fillColor: "rgba(220,220,220,0.2)",
                strokeColor: "rgba(220,220,220,1)",
                pointColor: "rgba(220,220,220,1)",
                pointStrokeColor: "#fff",
                pointHighlightFill: "#fff",
                pointHighlightStroke: "rgba(220,220,220,1)",
                data: [<?php echo $altitudeValues ?>]
            }
        ]
    };
    var ctx = document.getElementById("altitude").getContext("2d");
    var myNewChart = new Chart(ctx).Line(data);
    
    var data = {
        labels: [<?php echo $velocityLabels ?>],
        datasets: [
            {
                label: "Altitude",
                fillColor: "rgba(220,220,220,0.2)",
                strokeColor: "rgba(220,220,220,1)",
                pointColor: "rgba(220,220,220,1)",
                pointStrokeColor: "#fff",
                pointHighlightFill: "#fff",
                pointHighlightStroke: "rgba(220,220,220,1)",
                data: [<?php echo $velocityValues ?>]
            }
        ]
    };
    var ctx = document.getElementById("velocity").getContext("2d");
    var myNewChart = new Chart(ctx).Line(data);
</script>