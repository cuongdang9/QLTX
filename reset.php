<?php

		include 'connUpdate.php';
		
		$mathe = $_GET['mathe'];
		$dongdien = "0";
		$sotien = "0";
		$congsuat = "0";
		

		
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
					
					echo '{"Data":"RsOK"}';
											
			} 
			else 
			{

					echo '{"Data":"RsErr"}';
			}	
			
			
			
			
		 }
		 else
		 {
			
			echo '{"Data":"RsErr"}';

		 }
		 
		 $connect->close();
?>