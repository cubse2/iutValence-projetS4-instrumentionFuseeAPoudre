<?php
$fileErr = "";
if (isset ( $_POST ["submit"] )) {
	if (is_uploaded_file ( $_FILES ['donnees-file-to-import'] ['tmp_name'] )) {
		header ( "Location:tableau_bord_post_vol.php" );
	} else {
		$fileErr = "Un fichier est requis";
	}
}

?>
<!DOCTYPE html>
<html lang="fr-FR">
<head>
<title>Chargement des données</title>
<meta name="description"
	content="Extrait les donnéesdu fichier généré par l'application embarqué">
<meta charset="UTF-8">
<meta name="author" content="Baptiste Thevenet">
<link rel="stylesheet" type="text/css" href="skeleton.css">
<link rel="stylesheet" type="text/css" href="knacss.css">
<link rel="stylesheet" type="text/css" href="my_style.css">
<script src="//code.jquery.com/jquery-1.12.0.min.js"></script>
</head>
<body>
	<div class="main small-w100">
		<h1>Chargement des données</h1>
		<form enctype="multipart/form-data"
			action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]);?>"
			method="post">
			<input type="hidden" name="MAX_FILE_SIZE" value="30000" />
			<div class="grid-2">
				<div class="input-group flex-item-double">
					<div class="fileUpload button input-group-addon">
						<span class="floppy-open">&nbsp;&nbsp;&nbsp;</span> <input
							type="file" id="donnees-file-to-import"
							name="donnees-file-to-import" class="upload" />
					</div>
					<input class="fileUpload form-control" id="uploadFile"
						name="uploadFile" type="text"
						placeholder="Sélectionner un fichier" disabled="disabled" />
				</div>
				<span class="error flex-item-double"><?php echo $fileErr;?></span>
				<div>
					<input type="submit" value="OK" class="w100p" name="submit" />
				</div>
				<div>
					<a href="index.php" class="button w100p">Menu</a>
				</div>
			</div>
		</form>
	</div>
</body>
</html>
<script src="myScript.js"></script>

