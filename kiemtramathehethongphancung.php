<?php

		include 'connUpdate.php';
		
		$mathe = $_GET['mathe'];
		//$mathe  = '123456789';

		
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
			
			
			$sql = "SELECT  id, mathe , hoten, sdt  , biensoxe , dongdien , congsuat , sotien FROM dataesp32rfidacs712 WHERE id='$id'";
			
			
			
			$response1 = array();
		
			$result = $connect->query($sql);
			
			if ($result->num_rows >= 0) 
				{
					// output data of each row
					while($row = $result->fetch_assoc())
					 {
						 
						$response1['id'] = $row['id'];
						$response1['mathe'] = $row['mathe'];
						$response1['hoten'] = $row['hoten'];
						$response1['sdt'] = $row['sdt'];
						$response1['biensoxe'] = $row['biensoxe'];
						$response1['dongdien'] = $row['dongdien'];
						$response1['congsuat'] = $row['congsuat'];
						$response1['sotien'] = $row['sotien'];
						$response1['DataOK'] = "OK";
					 }
					 echo json_encode($response1);
					$result->free();
				} 
				else 
				{
					echo "{\"DataErr\":\"Err\"}";
				}
			
			
		 }
		 else
		 {
			
			echo "{\"DataErr\":\"Err\"}";

		 }
		 
		 $connect->close();
?>