<?php

		include 'connUpdate.php';
		
		$mathe = $_GET['mathe'];
		$dongdien = $_GET['dongdien'];
		$sotien = $_GET['sotien'];
		$congsuat = $_GET['congsuat'];
		
		//$mathe = "90697721";
		//$dongdien = "0.1";
		//$sotien = "0.2";
		//$congsuat = "0.3";
		
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
			
			
			$id = intval($response['id']);
			
			
			
			
			
			
			  
			  $queryResult = "UPDATE dataesp32rfidacs712 SET dongdien = '$dongdien' , congsuat = '$congsuat' , sotien = '$sotien' WHERE id='$id' ";
			  
			  
			  if ($connect->query($queryResult) == TRUE) 
			  {
					
					echo '{"UpdateOK":"OK"}';
											
			} 
			else 
			{

					echo '{"UpdateErr":"Err"}';
			}	
			
			
			
			
		 }
		 else
		 {
			
				echo '{"UpdateErr":"Err"}';

		 }
		 
		 $connect->close();
?>