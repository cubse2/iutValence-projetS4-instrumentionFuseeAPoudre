<?php

function loadFile(){

        if ($_FILES['file']['error'] != 0) {
            return "Une erreur c'est produite durant le transfert";
        }
        if(!move_uploaded_file($_FILES['file']['tmp_name'], "tmp/".FILE_FLIGHT_DATA)){
            return "Une erreur s'est produite durant la copie du fichier";
        }
        return TRUE;
}

if(isset($_POST['submit'])){
    if ($error = loadFile()){
        header("Location: tableau_bord_post_vol.php");
    }
}


?>
<!DOCTYPE html>
<html lang="fr-FR">
    <head>
        <title>Chargement des données</title>
        <meta name="description" content="Extrait les données du fichier généré par l'application embarqué">
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
            <form enctype="multipart/form-data" action="" method="post">
                <input type="hidden" name="MAX_FILE_SIZE" value="30000" />
                <div class="grid-2">
                     <div class="input-group flex-item-double">
                        <div class="fileUpload button input-group-addon">
                            <span class="floppy-open">&nbsp;&nbsp;&nbsp;</span>
                            <input type="file" id="donnees-file-to-import" name="importedFile" class="upload"/>
                        </div>
                        <input class="fileUpload form-control" id="uploadFile" type="text" placeholder="Sélectionner un fichier" disabled="disabled" />
                    </div>
                    <div><input type="submit" name="submit" value="OK" class="w100p"/></div>
                    <div><a href="index.php" class="button w100p">Menu</a></div>
                </div>
            </form>
        </div>
    </body>
</html>
<script src="myScript.js"></script>

