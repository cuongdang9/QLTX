<?php

		include 'connUpdate.php';
		
		$mathe = $_GET['mathe'];
		$hoten = $_GET['hoten'];
		$sdt = $_GET['sdt'];
		$biensoxe = $_GET['biensoxe'];
		$dongdien = $_GET['dongdien'];
		$congsuat = $_GET['congsuat'];
		$sotien = $_GET['sotien'];
	

		
		$foo = False;
		
		
		// kiểm tra mã thẻ  có tồn tại trong hệ thống không?
		
		$queryResult = $connect->query("SELECT * FROM dataesp32rfidacs712 WHERE  mathe = '$mathe'");
		
		
		$response = array();
		
		// hàm while xảy ra thì chắc mã thẻ đã tồn tại trong hệ thống
		
		while($fetchData=$queryResult ->fetch_assoc())
         {
			$response = $fetchData ; 		 
			 $foo = True;
	   			  
         }
		
		 
		 if($foo)
		 {
			// mã thẻ tồn tại trong hệ thống
			
			echo "{\"Data\":\"TheTonTai\"}";
			
			
			
		 }
		 else
		 {
			
			  $queryResult = "INSERT INTO dataesp32rfidacs712 (mathe , hoten, sdt  , biensoxe , dongdien , congsuat , sotien) VALUES ('$mathe', '$hoten' , '$sdt', '$biensoxe', '$dongdien', '$congsuat', '$sotien')";
			 
			 
			 if ($connect->query($queryResult) == TRUE) 
			 {
	
					echo "{\"Data\":\"AddOK\"}";
											
			} 
			else 
			{
					echo "{\"Data\":\"AddErr\"}";
			}

		 }
		 
		 $connect->close();
?>