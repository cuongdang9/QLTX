<?php

		include 'connUpdate.php';
		
		$mathe = $_GET['mathe'];
		$hoten = $_GET['hoten'];
		$sdt = $_GET['sdt'];
		$biensoxe = $_GET['biensoxe'];
		

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
			
			
			
			
			
			
			  
			  $queryResult = "UPDATE dataesp32rfidacs712 SET hoten = '$hoten' , sdt = '$sdt' , biensoxe = '$biensoxe' WHERE id='$id' ";
			  
			  
			  if ($connect->query($queryResult) == TRUE) 
			  {
					
					echo '{"Data":"SuaOK"}';
											
			} 
			else 
			{

					echo '{"Data":"SuaErr"}';
			}	
			
			
			
			
		 }
		 else
		 {
			
			echo '{"Data":"SuaErr"}';

		 }
		 
		 $connect->close();
?>