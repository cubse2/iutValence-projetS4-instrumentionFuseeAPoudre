<?php
?>
<!DOCTYPE html>
<html lang="fr-FR">
<head>
<title>Tableau de bord post-vol</title>
<meta name="description"
	content="Affichage des donn�es charg�es par l'application">
<meta charset="UTF-8">
<meta name="author" content="Baptiste Thevenet">
<link rel="stylesheet" type="text/css" href="skeleton.css">
<link rel="stylesheet" type="text/css" href="knacss.css">
<link rel="stylesheet" type="text/css" href="my_style.css">
<script src="//code.jquery.com/jquery-1.12.0.min.js"></script>
</head>
<body class='tableau-bord'>
	<a href='chargement_donnees.php' class='button w100p'>Retour</a>
	<div class="grid-2">
		<div class="window flex-item-double">
			<div class='flex-container'>
				<span class="flex-item-fluid">Données Chargées</span> <span
					class="w200p"><a href="#" class="button">Exporter les données</a></span>
			</div>
			<table>
				<thead>
					<tr>
						<th>Temps</th>
						<th>Vitesse axe z</th>
						<th>Accélération axe z</th>
						<th>Altitude</th>
					</tr>
				</thead>
				<tbody>
					<tr>
						<td>test Temps</td>
						<td>test Vitesse</td>
						<td>test Accélération</td>
						<td>test Altitude</td>
					</tr>
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
			</div>
		</div>
		<div class="window">
			<div class='flex-container'>
				<span class="flex-item-fluid">Accélération axe z en fonction du
					temps</span> <span class="w200p"><a href="#" class="button">Agrandir</a></span>
			</div>
		</div>
		<div class="window">
			<div class='flex-container'>
				<span class="flex-item-fluid">Vitesse axe z en fonction du temps</span>
				<span class="w200p"><a href="#" class="button">Agrandir</a></span>
			</div>
		</div>
	</div>
</body>
</html>
<script src="myScript.js"></script>