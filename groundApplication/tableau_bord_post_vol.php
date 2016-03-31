<?php
require_once 'config/config.php';
function __autoload($class) {
	require_once "class/$class.php";
}
function exportToCsv() {
	header ( 'Content-Description: File Transfer' );
	header ( 'Content-Type: application/octet-stream' );
	header ( 'Expires: 0' );
	header ( 'Cache-Control: must-revalidate' );
	header ( 'Pragma: public' );
	
	$postFlightMonitor = new postFlightMonitor ( new TimeStampedFileFlightDataStorage ( new TimeStampedFileFlightDataReader () ) );
    $time = $postFlightMonitor->createTimeTable();
	$altitude = $postFlightMonitor->createAltitudeTable();
	$velocity = $postFlightMonitor->createZVelocityTable();
	$acceleration = $postFlightMonitor->createZAccelerationTable();
	$file = fopen ( PATH_EXPORTED_FILE, 'w' );
	fputcsv ( $file, array (
			'temps (s)',
			'acceleration axe Z (m/s²)',
			'vitesse axe Z (m/s)',
			'altitude (m)' 
	), ';' );
	for($i = 0; $i < count ($time); $i ++) {
		fputcsv ( $file, array (
				$time[$i],
				$acceleration[$i],
				$velocity[$i],
				$altitude[$i] 
		), ';' );
	}
	fclose ( $file );
	header ( 'Content-Disposition: attachment; filename=' . EXPORTED_FILE );
	header ( 'Content-Length: ' . filesize ( PATH_EXPORTED_FILE ) );
	readfile ( PATH_EXPORTED_FILE );
	die ();
}

if (isset ( $_GET ['action'] ) && $_GET ['action'] == 'export_data') {
	exportToCsv ();
}

$postFlightMonitor = new postFlightMonitor ( new TimeStampedFileFlightDataStorage ( new TimeStampedFileFlightDataReader () ) );

$time = $postFlightMonitor->createTimeTable ();
$zAcceleration = $postFlightMonitor->createZAccelerationTable ();
$accelerationLabels = implode ( ',', $time );
$accelerationValues = implode ( ',', $zAcceleration );

$altitude = $postFlightMonitor->createAltitudeTable ();
$altitudeLabels = implode ( ',', $time );
$altitudeValues = implode ( ',', $altitude );

$zVelocity = $postFlightMonitor->createZVelocityTable ();
$velocityLabels = implode ( ',', $time );
$velocityValues = implode ( ',', $zVelocity );

$path3D = $postFlightMonitor->createPosition ();
$path3DX = implode ( ',', $path3D ['x'] );
$path3DY = implode ( ',', $path3D ['y'] );
$path3DZ = implode ( ',', $path3D ['z'] );
?>
<!DOCTYPE html>
<html lang="fr-FR">
<head>
<title>Tableau de bord post-vol</title>
<meta name="description"
	content="Affichage des données chargées par l'application">
<meta charset="UTF-8">
<meta name="author" content="Baptiste Thevenet">
<link rel="stylesheet" type="text/css" href="css/skeleton.css">
<link rel="stylesheet" type="text/css" href="css/knacss.css">
<link rel="stylesheet" type="text/css" href="css/my_style.css">
<script src="js/jquery-1.12.2.min.js"></script>
<script src="js/jquery.fullscreen-min.js"></script>
<script src="js/Chart.min.js"></script>
</head>
<body class='tableau-bord'>
	<a href='chargement_donnees.php' class='button w100p'>Retour</a>
	<div class="grid-2">
		<div class="window flex-item-double">
			<div class='grid-3-1'>
				<span class="opposite-button">Données Chargées</span> <span class="txtcenter"><a
					href="tableau_bord_post_vol.php?action=export_data" class="button">Exporter
						les données</a></span>
			</div>
			<div style="max-height: 300px; overflow-y: auto" class="graph-table">
				<table>
					<thead>
						<tr>
							<th>Temps (en s)</th>
							<th>Vitesse axe Z (m/s)</th>
							<th>Accélération axe Z (m/s²)</th>
							<th>Altitude (en m)</th>
						</tr>
					</thead>
					<tbody>
                    	<?php
						for($i = 0; $i < count ( $time ); $i ++) {
							echo "<tr>";
							echo "<td>", $time [$i], "</td>";
							echo "<td>", $zVelocity [$i], "</td>";
							echo "<td>", $zAcceleration [$i], "</td>";
							echo "<td>", $altitude [$i], "</td>";
						}
						?>
                	</tbody>
				</table>
			</div>
		</div>
		<div class="window">
			<div class='grid-3-1'>
				<span class="opposite-button">Trajectoire 3D</span> <span class=""><button
					class="button" onclick='$("#path").fullScreen(true)'>Agrandir</button></span>
				<div class="flex-item-double graph-table" id="path"></div>
			</div>
		</div>
		<div class="window">
			<div class='grid-3-1'>
				<span class="opposite-button">Altitude en fonction du temps</span> <span class=""><button
					class="button" onclick='$("#altitude").fullScreen(true)'>Agrandir</button></span>
				<canvas class="flex-item-double graph-table" id="altitude"></canvas>
			</div>
		</div>
		<div class="window">
			<div class='grid-3-1'>
				<span class="opposite-button">Accélération axe Z en fonction du temps</span> <span
					class=""><button class="button" onclick='$("#acceleration").fullScreen(true)'>Agrandir</button></span>

				<canvas class="flex-item-double graph-table" id="acceleration"></canvas>
			</div>
		</div>
		<div class="window">
			<div class='grid-3-1'>
				<span class="opposite-button">Vitesse axe Z en fonction du temps</span> <span
					class=""><button class="button" onclick='$("#velocity").fullScreen(true)'>Agrandir</button></span>
				<canvas class="flex-item-double graph-table" id="velocity"></canvas>
			</div>
		</div>
	</div>
</body>
</html>
<!--<script src="myScript.js"></script>-->
<script type="text/javascript"
	src="js/plotly-latest.min.js"></script>
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
    new Chart(ctx).LineAlt(data, options);

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
    
    var trace1 = {
    x: [<?php echo $path3DX ?>],
    y: [<?php echo $path3DY ?>],
    z: [<?php echo $path3DZ ?>],
    mode: 'lines',
    marker: {
        color: '#1f77b4',
        size: 12,
        symbol: 'circle',
        line: {
          color: 'rgb(0,0,0)',
          width: 0
        }
      },
      line: {
        color: '#1f77b4',
        width: 1
      },
      type: 'scatter3d'
    };
    var data = [trace1];
    var layout = {
      title: '3D Line Plot',
      autosize: false,
      width: 500,
      height: 500,
      margin: {
        l: 0,
        r: 0,
        b: 0,
        t: 65
      }
    };
    Plotly.newPlot('path', data, layout);
</script>