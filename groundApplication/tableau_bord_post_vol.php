<?php

require_once 'config/config.php';

function __autoload($class){
    require_once "class/$class.php";
}

function exportToCsv(){

    header('Content-Description: File Transfer');
    header('Content-Type: application/octet-stream');
    header('Expires: 0');
    header('Cache-Control: must-revalidate');
    header('Pragma: public');

    $postFlightMonitor = new postFlightMonitor(new TimeStampedFileFlightDataStorage(new TimeStampedFileFlightDataReader()));
    $altitude = $postFlightMonitor->createAltitudeAndTimeTable();
    $velocity = $postFlightMonitor->createVelocityYAndTimeTable();
    $acceleration = $postFlightMonitor->createYAccelerationAndTimeTable();
    $file = fopen(PATH_EXPORTED_FILE, 'w');
    fputcsv($file, array('temps', 'acceleration axe Y', 'vitesse axe Y', 'altitude'), ';');
    for ($i = 0; $i < count($altitude['time']); $i++){
        fputcsv($file, array($altitude['time'][$i], $acceleration['accelerationY'][$i], $velocity['velocityY'][$i], $altitude['altitude'][$i]), ';');
    }
    fclose($file);
    header('Content-Disposition: attachment; filename='.EXPORTED_FILE);
    header('Content-Length: ' . filesize(PATH_EXPORTED_FILE));
    readfile(PATH_EXPORTED_FILE);
    die();
}

if (isset($_GET['action']) && $_GET['action'] == 'export_data'){
    exportToCsv();
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

$path3D = $postFlightMonitor->createPosition();
?>
<!DOCTYPE html>
<html lang="fr-FR">
    <head>
        <title>Tableau de bord post-vol</title>
        <meta name="description"
              content="Affichage des données chargées par l'application">
        <meta charset="UTF-8">
        <meta name="author" content="Baptiste Thevenet">
        <link rel="stylesheet" type="text/css" href="skeleton.css">
        <link rel="stylesheet" type="text/css" href="knacss.css">
        <link rel="stylesheet" type="text/css" href="my_style.css">
        <script src="//code.jquery.com/jquery-1.12.0.min.js"></script>
        <script src="js/Chart.min.js"></script>
    </head>
    <body class='tableau-bord'>
        <a href='chargement_donnees.php' class='button w100p'>Retour</a>
        <div class="grid-2">
            <div class="window flex-item-double">
                <div class='flex-container'>
                    <span class="flex-item-fluid">Données Chargées</span> <span
                        class="w200p"><a href="tableau_bord_post_vol.php?action=export_data" class="button">Exporter les données</a></span>
                </div>
                <table>
                    <thead>
                        <tr>
                            <th>Temps</th>
                            <th>Vitesse axe Y</th>
                            <th>Accélération axe Y</th>
                            <th>Altitude</th>
                        </tr>
                    </thead>
                    <tbody>
                        <?php
                            for ($i = 0; $i < count($acceleration['time']); $i++){
                                echo "<tr>";
                                echo "<td>",$acceleration['time'][$i],"</td>";
                                echo "<td>",$velocity['velocityY'][$i],"</td>";
                                echo "<td>",$acceleration['accelerationY'][$i],"</td>";
                                echo "<td>",$altitude['altitude'][$i],"</td>";
                            }
                        ?>
                    </tbody>
                </table>
            </div>
            <div class="window">
                <div class='flex-container'>
                    <span class="flex-item-fluid">Trajectoire 3D</span> <span
                        class="w200p"><a href="#" class="button">Agrandir</a></span>
                </div>
            </div>
            <div class="window">
                <div class='flex-container'>
                    <span class="flex-item-fluid">Altitude en fonction du temps</span> <span
                        class="w200p"><a href="#" class="button">Agrandir</a></span>
                    <canvas id="altitude"></canvas>
                </div>
            </div>
            <div class="window">
                <div class='flex-container'>
				<span class="flex-item-fluid">Accélération axe Y en fonction du
					temps</span> <span class="w200p"><a href="#" class="button">Agrandir</a></span>
                </div>
                <canvas id="acceleration"></canvas>
            </div>
            <div class="window">
                <div class='flex-container'>
                    <span class="flex-item-fluid">Vitesse axe Y en fonction du temps</span>
                    <span class="w200p"><a href="#" class="button">Agrandir</a></span>
                    <canvas id="velocity"></canvas>
                </div>
            </div>
        </div>
    </body>
</html>
<!--<script src="myScript.js"></script>-->
<script>
    Chart.types.Line.extend({
        name: "LineAlt",
        initialize: function (data) {
            Chart.types.Line.prototype.initialize.apply(this, arguments);
            var xLabels = this.scale.xLabels
            xLabels.forEach(function (label, i) {
                if (i % 10 != 1)
                    xLabels[i] = '';
            })
        }
    });

    var options = {
        responsive: true,
        scaleBeginAtZero: true,
        scaleShowGridLines: true,
        scaleGridLineColor: "rgba(0,0,0,.05)",
        scaleGridLineWidth: 1
    };
    var data = {
        labels: [<?php echo $accelerationLabels ?>],
        datasets: [
            {
                label: "Accélération Y",
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
    new Chart(ctx).LineAlt(data, options);
    
    var data = {
        labels: [<?php echo $velocityLabels ?>],
        datasets: [
            {
                label: "Velocity Y",
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
    new Chart(ctx).LineAlt(data, options);
</script>