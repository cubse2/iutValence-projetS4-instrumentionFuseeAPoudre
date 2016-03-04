<?php
$speed = $port = "";
$speedErr = $portErr = "";
if ($_SERVER ["REQUEST_METHOD"] == "POST") {
	if (empty ( $_POST ["speed"] )) {
		$speedErr = "Une vitesse de transmission est requise";
	} else {
		$speed = $_POST ["speed"];
	}
	if (empty ( $_POST ["port"] )) {
		$portErr = "Un port est requis";
	} else {
		$port = $_POST ["port"];
	}
	if ($speedErr == "" && $portErr == "") {
		header ( "Location:tableau_bord_en_vol.php" );
	}
}
?>
<!DOCTYPE html>
<html lang="fr-FR">
<head>
<title>Menu</title>
<meta name="description" content="Etablit la connexion avec l'Arduino">
<meta charset="UTF-8">
<meta name="author" content="Baptiste Thevenet">
<link rel="stylesheet" type="text/css" href="skeleton.css">
<link rel="stylesheet" type="text/css" href="knacss.css">
<link rel="stylesheet" type="text/css" href="my_style.css">
<script src="//code.jquery.com/jquery-1.12.0.min.js"></script>
</head>
<body>
	<div class="main small-w100">
		<h1>Connexion à l'Arduino</h1>
		<form action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]);?>"
			method="post">
			<div class="grid-2">
				<div class="input-group flex-item-double">
					<p>
						Vitesse de transmission</br> <input type="number" name="speed"
							value="<?php echo $speed;?>">
					</p>
					<span class="error"><?php echo $speedErr;?></span>
					<p>
						Port</br> <input type="number" name="port"
							value="<?php echo $port;?>">
					</p>
					<span class="error"><?php echo $portErr;?></span>
				</div>
				<div>
					<input type="submit" value="OK" class="w100p" />
				</div>
				<div>
					<a href="index.php" class="button w100p">Menu</a>
				</div>
			</div>
		</form>
	</div>
</body>
</html>