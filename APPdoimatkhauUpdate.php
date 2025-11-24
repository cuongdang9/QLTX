<?php
		include 'connUpdate.php';
		$mathe = $_POST['mathe'];
		//$password = $_POST['password'];
		//$passwordupdate = $_POST['passwordupdate'];
			
		$foo = False;
		
		//$queryResult = $connect->query("SELECT * FROM user WHERE  mathe= '$mathe'  AND  pass='$password' ");
		$queryResult = $connect->query("SELECT * FROM dataesp32rfidacs712 WHERE  mathe= '$mathe' ");
			
		$response = array();
			
		 // hàm while xảy ra chắc chắn đã kiểm tra dữ liệu username và password có tồn tại trong hệ thống => update password
		
		while($fetchData=$queryResult ->fetch_assoc())
         {
			 
			 // đọc data username password đúng hàng đó đưa vào chuỗi json
              $response = $fetchData ; 
			  // hiển thị chuỗi json
			  //echo json_encode($response);
			  
			  // cho True để updatepassword
			  
			  $foo = True;		    				  
         }	 
		 if($foo)
		 {
			// echo ("UPDATE password");
			 // lấy dữ liệu id hàng dữ liệu so sánh đúng để update password mới 		  
			 $id = intval($response['id']); 
			 //echo ('------------------------------');
			  //echo ('id = ');
			// echo ($id);		  
			  $queryResult = "UPDATE user SET pass = '$passwordupdate' WHERE id='$id' ";
			  
			  
			  if ($connect->query($queryResult) == TRUE) 
			  {
				   // Update passwold thành công
					echo "E";							
			} 
			else 
			{
				    // Update passwold lỗi
					echo "F";
			}	
		 }
		 else
		 {
			 // username password nhập sai
			  echo "G";
		 }
		 $connect->close();
	

?>
