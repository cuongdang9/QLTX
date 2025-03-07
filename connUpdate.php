<?php

	$servername = "localhost"; // 
    $username = "root";
    $password = "";        
    $dbname = "dataesp32";

$connect = new mysqli($servername, $username, $password, $dbname);

 if ($connect) 
 {
    //echo "Connect ";
 } 
 
 else
{
	echo "Failed Connect";
	exit();
}

?>