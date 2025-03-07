<?php

		include 'connUpdate.php';
		
		$mathe = $_GET['mathe'];
		//$mathe = "123456789";
	
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
			
			
			$sql = "DELETE   FROM dataesp32rfidacs712 WHERE id='$id'";
			
			
			if ($connect->query("DELETE FROM dataesp32rfidacs712 WHERE id='$id'")) 
			{
					echo "{\"Data\":\"ClearOK\"}";
			}
			
		 }
		 else
		 {
			
			echo "{\"Data\":\"ClearErr\"}";

		 }
		 
		 $connect->close();
?>