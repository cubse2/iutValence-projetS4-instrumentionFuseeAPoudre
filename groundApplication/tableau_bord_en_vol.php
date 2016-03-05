<?php
$etat = "Prêt à démarrer";
$temps = $vitesse = $acceleration = $altitude = 0;
?>
<!DOCTYPE html>
<html lang="fr-FR">
    <head>
        <title>Tableau de bord post-vol</title>
        <meta name="description" content="Affichage des données en temps réel">
        <meta charset="UTF-8">
        <meta name="author" content="Baptiste Thevenet">
        <link rel="stylesheet" type="text/css" href="skeleton.css">
        <link rel="stylesheet" type="text/css" href="knacss.css">
        <link rel="stylesheet" type="text/css" href="my_style.css">
        <script src="//code.jquery.com/jquery-1.12.0.min.js"></script>
    </head>
    <body class='tableau-bord'>
        <a href='connexion_arduino.php' class='button w100p'>Retour</a>
        <input type="button" value="Lancer la transmission" />
        <input type="button" value="Arrêter la transmission" />
        <div class="window">
            Etat de la transmission : <?php echo $etat;?>
        </div>
        <div class="grid-4">
            <div class="window">
                Temps : <?php echo $temps;?> s
            </div>
            <div class="window">
                Vitesse axe z : <?php echo $vitesse;?> m/s
            </div>
            <div class="window">
                Accélération axe z : <?php echo $acceleration;?> m/s
            </div>
            <div class="window">
                Altitude : <?php echo $altitude;?> m
            </div>
        </div>
        <div class="window">
            <strong>Altitude en fonction du temps</strong>
        </div>
    </body>
</html>
<!-- <script src="myScript.js"></script> -->