const char index_smartphone[] PROGMEM = R"rawliteral(


<!DOCTYPE html> 
  <html>
   <head> 
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">

       <title>ĐỒ ÁN TỐT NGHIỆP</title> 
       <style> 
          body {
     

      text-align:center;
      background-color:  #a6a6a6;
    
      font-family: Times New Roman;
      }

         
     
      
   
      

      
     
      
     
      
      
       
      .button {
        display: inline-block;
        padding: 10px 10px;
        font-size: 10px;
        cursor: pointer;
        text-align: center;
        text-decoration: none;
        outline: none;
        color: back;
        background-color: #d9d9d9;

        border-radius: 20px;
        box-shadow: 0 5px #999;
        height:30px; 
        width:100px;
        border: solid 2px blue;
      }

      .button:hover {background-color: #33ff33}

      .button:active {
        background-color: #ff0000;
        box-shadow: 0 5px #666;
        transform: translateY(4px);
      }
      
      
      tr
      {
        background-color:#ffff00;
        color:white;
        -moz-border-radius:10px;
        -webkit-border-radius:10px;
        border-radius:10px
      }
      th    
      {
       
        -moz-border-radius:10px;
        -webkit-border-radius:10px;
        border-radius:10px
        border: solid 5px Blue;
      }
      td    
      {
       
        -moz-border-radius:10px;
        -webkit-border-radius:10px;
        border-radius:10px
        border: solid 5px Blue;
      }


     
      table, th, td {
          border: 3px solid black;
        
    }
    
    






       </style>
       <meta name="viewport" content="width=device-width,user-scalable=0" charset="UTF-8">
   </head>
   
    <script>
    var checkthe = false;
    var checkone = 0;
    var myTimeout = 0;
    var myVar;
    var myVar1;
    var myVar2;
    var StartStop = true;
    var loadform = 0;
    
    
        function UpdateData(){
    
    var xhttp = new XMLHttpRequest();
      
     
      xhttp.onreadystatechange = function (){
     
         if(this.readyState == 4 && this.status == 200)
         {
         
         
        var DataVDK  = xhttp.responseText;        
          
        console.log("Dữ liệu VDK:" + DataVDK);
           
        var DataJson = JSON.parse(DataVDK); 
           
        
        
            if(DataJson.MaThe == "null")
            {
              document.getElementById("thongbao").innerHTML = "Vui Lòng Quét Thẻ";
            }
            else 
            {
              document.getElementById("thongbao").innerHTML = "Kiểm tra thẻ!!!";
              document.getElementById("mathe").value = DataJson.MaThe;
              
              
              if(DataJson.RL == "0")  
              {
                console.log("Kiểm tra thẻ MYSQL");
                KiemTraThe();
              }
              else if(DataJson.RL == "1") 
              {
                DieuKhienRelay();
              }
                    
            }
        
        
        if(DataJson.RL == "1")  
              {
                document.getElementById("mathe").value = DataJson.MaThe1;
              }
              else
              {
                document.getElementById("mathe").value = "";
              }
        
        
        if(DataJson.hoten != null)
        {
        document.getElementById("hoten").value = DataJson.hoten;
        }
        
         if(DataJson.sdt != null)
        {
        document.getElementById("sdt").value = DataJson.sdt;
        }
        
         if(DataJson.biensoxe != null)
        {
        document.getElementById("biensoxe").value = DataJson.biensoxe;
        }
        
         if(DataJson.dongdien != null)
        {
        document.getElementById("dongdien").value = DataJson.dongdien;
        }
        
       if(DataJson.congsuat != null)
        {
        document.getElementById("congsuat").value = DataJson.congsuat;
        }  

        if(DataJson.sotien != null)
        {
        document.getElementById("sotien").value = DataJson.sotien;
        } 
        if(DataJson.RL == "1")
            {
          
            document.getElementById("RL").innerHTML = "ĐANG BẬT";

            }
            else if(DataJson.RL == "0")
            {
            
            document.getElementById("RL").innerHTML = "ĐANG TẮT";
            }
          
      
        }
       
      };
      
      xhttp.open('GET','/Update',true);
      xhttp.send(); 
    myVar = setTimeout(function(){ 
      UpdateData() ;
     }, 2000); 
    
    
    
    
      
    }
       
  function KiemTraMySQL()
  {
    
  
    var xhttp = new XMLHttpRequest();
      
      xhttp.onreadystatechange = function (){
     
         if(this.readyState == 4 && this.status == 200)
         {
         
         
        var DataVDKKiemTra  = xhttp.responseText;        
          
        console.log("Dữ liệu VDK Kiểm tra:" + DataVDKKiemTra);
        
        var DataJsonKiemTra = JSON.parse(DataVDKKiemTra); 
        
        if(DataJsonKiemTra.Data == "null")
        {
        console.log("Không có dữ liệu hệ thống");
        document.getElementById("thongbao").innerHTML = "Không có dữ liệu!!!";
        checkthe = true;
        
        
        }
        else if(DataJsonKiemTra.Data == "Err")
        {
        console.log("Không có dữ liệu hệ thống");
        document.getElementById("thongbao").innerHTML = "Không có dữ liệu!!!";
        checkthe = true;
        }
        
        if(DataJsonKiemTra.mathe != null)
        {
        document.getElementById("mathe").value = DataJsonKiemTra.mathe;
        document.getElementById("thongbao").innerHTML = "Dữ liệu OK!!!";
        DieuKhienRelay();
        }
        
        if(DataJsonKiemTra.hoten != null)
        {
        document.getElementById("hoten").value = DataJsonKiemTra.hoten;
        }
        
         if(DataJsonKiemTra.sdt != null)
        {
        document.getElementById("sdt").value = DataJsonKiemTra.sdt;
        }
        
         if(DataJsonKiemTra.biensoxe != null)
        {
        document.getElementById("biensoxe").value = DataJsonKiemTra.biensoxe;
        }
        
         if(DataJsonKiemTra.dongdien != null)
        {
        document.getElementById("dongdien").value = DataJsonKiemTra.dongdien;
        }
        
       if(DataJsonKiemTra.congsuat != null)
        {
        document.getElementById("congsuat").value = DataJsonKiemTra.congsuat;
        }  

        if(DataJsonKiemTra.sotien != null)
        {
        document.getElementById("sotien").value = DataJsonKiemTra.sotien;
        } 

          
        }
       
      };  
    var data = document.getElementById("mathe").value;
     xhttp.open('GET',"/KiemTra?Json="+data,true);
    xhttp.send(); 
  
    
  }
  
  function KiemTraThe()
  {
    document.getElementById("thongbao").innerHTML = ".....";
    document.getElementById("hoten").value = "";
    document.getElementById("sdt").value = "";
    document.getElementById("biensoxe").value = "";
    document.getElementById("dongdien").value = "";
    document.getElementById("congsuat").value = "";
    document.getElementById("sotien").value = "";
    var data_the = document.getElementById("mathe").value;
    console.log("data_the:"+data_the);
    
    
    KiemTraMySQL();
    
    
  }
  function ThemThe()
  {
    var thongbao = document.getElementById("thongbao").innerHTML;
    
      var mathe = document.getElementById("mathe").value;
      var hoten = document.getElementById("hoten").value;
      var sdt = document.getElementById("sdt").value;
      var biensoxe = document.getElementById("biensoxe").value;
      var dongdien = "0";
      var congsuat = "0";
      var sotien = "0";
      
      var TX = "{\"mathe\":\""+mathe+"\",\"hoten\":\""+hoten+"\",\"sdt\":\""+sdt+"\",\"biensoxe\":\""+biensoxe+"\",\"dongdien\":\""+dongdien+"\",\"congsuat\":\""+congsuat+"\",\"sotien\":\""+sotien+"\"}";
      
      var xhttp = new XMLHttpRequest();
    
      
        xhttp.onreadystatechange = function (){
       
         if(this.readyState == 4 && this.status == 200)
         {
          var DataVDKThemThe  = xhttp.responseText;        
          
          console.log("Dữ liệu DataVDKThemThe:" + DataVDKThemThe);
          
          var DataJsonThemThe = JSON.parse(DataVDKThemThe); 
          
          if(DataJsonThemThe.Data == "TheTonTai")
            {
            console.log("Thẻ Đã tồn tại");
            document.getElementById("thongbao").innerHTML = "Thẻ Đã tồn tại";
        
            
            
            }
            else if(DataJsonThemThe.Data == "AddOK")
            {
            console.log("Thêm Thẻ Thành Công");
            document.getElementById("thongbao").innerHTML = "Thêm Thẻ Thành Công!!!";
          
            }
            else if(DataJsonThemThe.Data == "AddErr")
            {
            console.log("Thêm Thẻ Lỗi");
            document.getElementById("thongbao").innerHTML = "Thêm Thẻ Lỗi!!!";
          
            }
          
         }
      };
      xhttp.open('GET',"/ThemThe?Json="+TX,true);
      xhttp.send(); 
    
  }
  
  function DieuKhienRelay()
  {
    var xhttp = new XMLHttpRequest();
    var mathe = document.getElementById("mathe").value;
    var dongdien = document.getElementById("dongdien").value;
    var congsuat = document.getElementById("congsuat").value;
    var sotien = document.getElementById("sotien").value;
    var TX = "{\"mathe\":\""+mathe+"\",\"dongdien\":\""+dongdien+"\",\"congsuat\":\""+congsuat+"\",\"sotien\":\""+sotien+"\"}";

    xhttp.onreadystatechange = function (){
       
        if(this.readyState == 4 && this.status == 200)
        {
          var DataVDKRelay  = xhttp.responseText;        
          
          console.log("Dữ liệu DataVDKRelay:" + DataVDKRelay);
          
          var DataJsonRelay = JSON.parse(DataVDKRelay); 
          
          if(DataJsonRelay.RL == "1")
            {
            console.log("Relay ON!!!!");
            document.getElementById("RL").innerHTML = "ĐANG BẬT";

            }
            else if(DataJsonRelay.RL == "0")
            {
            console.log("Relay OFF!!!!");
            document.getElementById("RL").innerHTML = "ĐANG TẮT";
            
        
            document.getElementById("hoten").value = "";
            document.getElementById("sdt").value = "";
            document.getElementById("biensoxe").value = "";
            document.getElementById("dongdien").value = "";
            document.getElementById("congsuat").value = "";
            document.getElementById("sotien").value = "";
          
            }
        }
    };
    xhttp.open('GET',"/Relay?Json="+TX,true);
    xhttp.send(); 
  }
  
  
  
  function LoadForm()
  {
    console.log("LoadForm");
    document.getElementById("phonghethong").style.display = "block";
        document.getElementById("phongthemvaxoathe").style.display = "none";
  
  
  }
  
  function ThemXoaThe()
  {
    var TT_RL = document.getElementById("RL").innerHTML;
    if(TT_RL == "ĐANG BẬT")
    {
      alert("Hệ thống đang chạy không thể thao tác!!!");
      return;
    }
    if(loadform == 0)
    {
      if (confirm('Bạn muốn Thêm Sửa Xóa Thẻ???')) {
  
        console.log('OK tôi muốn Thêm Sửa Xóa Thẻ');
        clearTimeout(myVar);
        document.getElementById("phonghethong").style.display = "none";
        document.getElementById("phongthemvaxoathe").style.display = "block";
        loadform = 1;
        UpdateDataThemSuaXoa();
        
        
      } 
      else 
      {
        
        console.log('Không muốn Thêm Sửa Xóa Thẻ');
        document.getElementById("phonghethong").style.display = "block";
        document.getElementById("phongthemvaxoathe").style.display = "none";
        loadform = 0;
      }
    }
    else if(loadform == 1)
    {
      if (confirm('Bạn muốn Thoát???')) {
  
        console.log('OK tôi muốn Thoát');
        clearTimeout(myVar2);
        UpdateData();
        document.getElementById("phonghethong").style.display = "block";
        document.getElementById("phongthemvaxoathe").style.display = "none";
        loadform = 0;
        
      } 
      else 
      {
        
        console.log('Không muốn Thoát');
        document.getElementById("phonghethong").style.display = "none";
        document.getElementById("phongthemvaxoathe").style.display = "block";
        loadform = 1;
      }
    }
    
  }
  
  function Start()
  {
    LoadForm();
    UpdateData();
    
  }
  
  function UpdateDataThemSuaXoa()
  {
    var xhttp = new XMLHttpRequest();
      
     
      xhttp.onreadystatechange = function (){
     
         if(this.readyState == 4 && this.status == 200)
         {
         
         
        var DataVDKThemSuaXoa  = xhttp.responseText;        
          
        console.log("Dữ liệu DataVDKThemSuaXoa:" + DataVDKThemSuaXoa);
           
        var DataJsonThemSuaXoa = JSON.parse(DataVDKThemSuaXoa); 
           
        
        if(DataJsonThemSuaXoa.MaThe == "null")
        {
          document.getElementById("thongbaothemsuaxoa").innerHTML = "Vui Lòng Quét Thẻ";
          
        }
        else 
        {
          document.getElementById("thongbaothemsuaxoa").innerHTML = "Kiểm tra thẻ!!!";
          document.getElementById("mathethemsuaxoa").value = DataJsonThemSuaXoa.MaThe;
          KiemTraTheThemSuaXoa();
          
        }
      
        }
       
      };
      
      xhttp.open('GET','/UpdateThemSuaXoa',true);
      xhttp.send(); 
    myVar2 = setTimeout(function(){ 
      UpdateDataThemSuaXoa() ;
     }, 2000); 
  }
  
  function KiemTraTheThemSuaXoa()
  {
    //clearTimeout(myVar2);
    console.log("run KiemTraTheThemSuaXoa");
    
    var data_the = document.getElementById("mathethemsuaxoa").value;
    console.log("data_the:"+data_the);
    
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function (){
     
         if(this.readyState == 4 && this.status == 200)
         {
         
         
        var DataKiemTraTheThemSuaXoa = xhttp.responseText;        
          
        console.log("Dữ liệu DataKiemTraTheThemSuaXoa:" + DataKiemTraTheThemSuaXoa);
           
        var DataJsonKiemTraTheThemSuaXoa = JSON.parse(DataKiemTraTheThemSuaXoa); 
        
        if(DataJsonKiemTraTheThemSuaXoa.Data == "null")
        {
        
        document.getElementById("hotenthemsuaxoa").value = "";
        document.getElementById("sdtthemsuaxoa").value = "";
        document.getElementById("biensoxethemsuaxoa").value = "";
        document.getElementById("dongdienthemsuaxoa").value = "";
        document.getElementById("congsuatthemsuaxoa").value = "";
        document.getElementById("sotienthemsuaxoa").value = "";
        }
       
       if(DataJsonKiemTraTheThemSuaXoa.hoten != null)
        {
        document.getElementById("hotenthemsuaxoa").value = DataJsonKiemTraTheThemSuaXoa.hoten;
        document.getElementById("btnthem").disabled = true;
        document.getElementById("btnsua").disabled = false;
        document.getElementById("btnxoa").disabled = false;
        
        }
        else
        {
        document.getElementById("btnthem").disabled = false;
        document.getElementById("btnsua").disabled = true;
        document.getElementById("btnxoa").disabled = true;
        }
        
         if(DataJsonKiemTraTheThemSuaXoa.sdt != null)
        {
        document.getElementById("sdtthemsuaxoa").value = DataJsonKiemTraTheThemSuaXoa.sdt;
        }
        
         if(DataJsonKiemTraTheThemSuaXoa.biensoxe != null)
        {
        document.getElementById("biensoxethemsuaxoa").value = DataJsonKiemTraTheThemSuaXoa.biensoxe;
        }
        
         if(DataJsonKiemTraTheThemSuaXoa.dongdien != null)
        {
        document.getElementById("dongdienthemsuaxoa").value = DataJsonKiemTraTheThemSuaXoa.dongdien;
        }
        
       if(DataJsonKiemTraTheThemSuaXoa.congsuat != null)
        {
        document.getElementById("congsuatthemsuaxoa").value = DataJsonKiemTraTheThemSuaXoa.congsuat;
        }  

        if(DataJsonKiemTraTheThemSuaXoa.sotien != null)
        {
        document.getElementById("sotienthemsuaxoa").value = DataJsonKiemTraTheThemSuaXoa.sotien;
        } 
        
        
      
        }
       
      };
    

    xhttp.open('GET',"/KiemTraTheThemSuaXoa?Json="+data_the,true);
    xhttp.send(); 
    
  }
  function BtnKiemTra()
  {
    document.getElementById("btnthem").disabled = false;
    document.getElementById("btnsua").disabled = false;
    document.getElementById("btnxoa").disabled = false;
    document.getElementById("thongbaothemsuaxoa").innerHTML = ".....";
    document.getElementById("mathethemsuaxoa").value = "";
    document.getElementById("hotenthemsuaxoa").value = "";
    document.getElementById("sdtthemsuaxoa").value = "";
    document.getElementById("biensoxethemsuaxoa").value = "";
    document.getElementById("dongdienthemsuaxoa").value = "";
    document.getElementById("congsuatthemsuaxoa").value = "";
    document.getElementById("sotienthemsuaxoa").value = "";
    UpdateDataThemSuaXoa();
  }
  function BtnThem()
  {
    if (confirm('Bạn muốn Thêm Thẻ???')) {
  
        console.log('OK tôi muốn Thêm Thẻ');
        
      } 
      else 
      {
        
        console.log('Không muốn Thêm  Thẻ');
        return;
      }
    var mathe = document.getElementById("mathethemsuaxoa").value;
    var hoten =  document.getElementById("hotenthemsuaxoa").value;
    var sdt =  document.getElementById("sdtthemsuaxoa").value;
    var biensoxe =  document.getElementById("biensoxethemsuaxoa").value;
    var dongdien = "0";
    var congsuat = "0";
    var sotien = "0";
    if(mathe == "")
    {
      alert("Chưa có thông tin mã thẻ không thể thêm???");
      return;
    }
    if(hoten == "")
    {
      alert("Vui Lòng nhập họ tên???");
      return;
    }
    if(sdt == "")
    {
      alert("Vui Lòng nhập Số điện thoại???");
      return;
    }
    if(biensoxe == "")
    {
      alert("Vui Lòng nhập biển số xe???");
      return;
    }
    
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function (){
     
         if(this.readyState == 4 && this.status == 200)
         {
         
         
        var DataThemThe = xhttp.responseText;        
          
        console.log("Dữ liệu DataThemThe:" + DataThemThe);
           
        var DataJsonThemThe = JSON.parse(DataThemThe); 
        
        if(DataJsonThemThe.Data == "AddOK")
        {
        alert("Thêm Thẻ Thành Công!!!");
        document.getElementById("mathethemsuaxoa").value = "";
        document.getElementById("hotenthemsuaxoa").value = "";
        document.getElementById("sdtthemsuaxoa").value = "";
        document.getElementById("biensoxethemsuaxoa").value = "";
        }
        else  if(DataJsonThemThe.Data == "AddErr")
        {
        alert("Thêm Thẻ Lỗi!!!");
        document.getElementById("mathethemsuaxoa").value = "";
        document.getElementById("hotenthemsuaxoa").value = "";
        document.getElementById("sdtthemsuaxoa").value = "";
        document.getElementById("biensoxethemsuaxoa").value = "";
        }
      }
    };
    var TX = "{\"mathe\":\""+mathe+"\",\"hoten\":\""+hoten+"\",\"sdt\":\""+sdt+"\",\"biensoxe\":\""+biensoxe+"\",\"dongdien\":\""+dongdien+"\",\"congsuat\":\""+congsuat+"\",\"sotien\":\""+sotien+"\"}";

    xhttp.open('GET',"/ThemThe?Json="+TX,true);
    xhttp.send(); 
    
    
  }
  function BtnXoa()
  {
    if (confirm('Bạn muốn Xóa Thẻ???')) {
  
        console.log('OK tôi muốn Xóa Thẻ');
        
      } 
      else 
      {
        
        console.log('Không muốn Xóa  Thẻ');
        return;
      }
      
    var mathe = document.getElementById("mathethemsuaxoa").value;
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function (){
     
         if(this.readyState == 4 && this.status == 200)
         {
         
         
        var DataXoaThe = xhttp.responseText;        
          
        console.log("Dữ liệu DataXoaThe:" + DataXoaThe);
           
        var DataJsonXoaThe = JSON.parse(DataXoaThe); 
        
        if(DataJsonXoaThe.Data == "ClearOK")
        {
        alert("Xóa Thẻ Thành Công!!!");
        document.getElementById("mathethemsuaxoa").value = "";
        document.getElementById("hotenthemsuaxoa").value = "";
        document.getElementById("sdtthemsuaxoa").value = "";
        document.getElementById("biensoxethemsuaxoa").value = "";
        }
        else  if(DataJsonThemThe.Data == "ClearErr")
        {
        alert("Xóa Thẻ Lỗi!!!");
        document.getElementById("mathethemsuaxoa").value = "";
        document.getElementById("hotenthemsuaxoa").value = "";
        document.getElementById("sdtthemsuaxoa").value = "";
        document.getElementById("biensoxethemsuaxoa").value = "";
        }
      }
    };
    xhttp.open('GET',"/XoaThe?Json="+mathe,true);
    xhttp.send(); 
  }
  function BtnSua()
  {
    if (confirm('Bạn muốn Sửa Thông tin???')) {
  
        console.log('OK tôi muốn Sửa thong tin');
        
      } 
      else 
      {
        
        console.log('Không muốn Sửa thong tin');
        return;
      }
    var mathe = document.getElementById("mathethemsuaxoa").value;
    var hoten =  document.getElementById("hotenthemsuaxoa").value;
    var sdt =  document.getElementById("sdtthemsuaxoa").value;
    var biensoxe =  document.getElementById("biensoxethemsuaxoa").value;
    
    
    var TX = "{\"mathe\":\""+mathe+"\",\"hoten\":\""+hoten+"\",\"sdt\":\""+sdt+"\",\"biensoxe\":\""+biensoxe+"\"}";

    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function (){
     
         if(this.readyState == 4 && this.status == 200)
         {
         
         
        var DataSuaThe = xhttp.responseText;        
          
        console.log("Dữ liệu DataSuaThe:" + DataSuaThe);
           
        var DataJsonSuaThe = JSON.parse(DataSuaThe); 
        
        if(DataJsonSuaThe.Data == "SuaOK")
        {
        alert("Xóa Thẻ Thành Công!!!");

        }
        else  if(DataJsonSuaThe.Data == "SuaErr")
        {
        alert("Xóa Thẻ Lỗi!!!");

        }
      }
    };
    xhttp.open('GET',"/SuaThe?Json="+TX,true);
    xhttp.send(); 
  }
  
  function BtnReset()
  {
    if (confirm('Bạn muốn Reset Thông tin???')) {
  
        console.log('OK tôi muốn Reset thong tin');
        
      } 
      else 
      {
        
        console.log('Không muốn Reset thong tin');
        return;
      }
    var mathe = document.getElementById("mathethemsuaxoa").value;
  
    var TX = mathe;
    
      var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function (){
     
         if(this.readyState == 4 && this.status == 200)
         {
         
         
        var DataReSet = xhttp.responseText;        
          
        console.log("Dữ liệu DataReSet:" + DataReSet);
           
        var DataJsonReSet = JSON.parse(DataReSet); 
        
        if(DataJsonReSet.Data == "RsOK")
        {
        alert("Reset Thành Công!!!");

        }
        else  if(DataJsonReSet.Data == "RsErr")
        {
        alert("Reset Lỗi!!!");

        }
      }
    };
    xhttp.open('GET',"/Reset?Json="+TX,true);
    xhttp.send(); 

  }
     </script>
   <body onload = "Start()"> 
     
      
    <table width="800px" height="auto" border="2" cellpadding="10" align="center" >
              
        <tr>
                       
              <td colspan="6" width="50px"> 
        <center> 
          <img width="750px" height="200px" src="data:image/png;base64,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">
        </center> 
             </td> 
       
    

                    
                                 
        </tr>
    
    </table>
    
    
    <div id = "phonghethong">
  
          <table width="800px" height="auto" border="2" cellpadding="10" align="center" >
              
      
         
         
    
         
      
      
      
       <tr  height="50" > 
         <td colspan="3" > <center> <span style = "color: Blue"> <b> THÔNG TIN HỆ THỐNG</b> </span> </center> </td>  
           
        </tr>
        
        <tr> 
         <td colspan="1" > <center> <span style = "color: Blue"> <b> THÔNG BÁO</b> </span> </center> </td>  
          <td colspan="2"  align='left'> 
          
            <center> <span id="thongbao"style = "color: Blue"> <b> ....</b> </span> </center>
           </td> 
          </td>  
        </tr>
      
         <tr> 
         <td colspan="1" > <center> <span style = "color: Blue"> <b> MÃ THẺ</b> </span> </center> </td>  
          <td colspan="2"  align='left'> 
          
           <input id="mathe" style="height:30px; width:240px" align="left" readonly> 
           </td> 
          </td>  
        </tr>
        
          <tr> 
         <td colspan="1" > <center> <span style = "color: Blue"> <b> HỌ TÊN</b> </span> </center> </td>  
          <td colspan="2"  align='left'> 
          
           <input id="hoten" style="height:30px; width:240px" align="left"> 
           </td> 
          </td>  
        </tr>
        
        
         <tr> 
         <td colspan="1" > <center> <span style = "color: Blue"> <b> SỐ ĐIỆN THOẠI</b> </span> </center> </td>  
          <td colspan="2"  align='left'> 
          
           <input id="sdt" style="height:30px; width:240px" align="left"> 
           </td> 
          </td>  
        </tr>
        
          <tr> 
         <td colspan="1" > <center> <span style = "color: Blue"> <b> BIỂN SỐ XE</b> </span> </center> </td>  
          <td colspan="2"  align='left'> 
          
           <input id="biensoxe" style="height:30px; width:240px" align="left"> 
           </td> 
          </td>  
        </tr>
        
      <tr> 
         <td colspan="1" > <center> <span style = "color: Blue"> <b> DÒNG ĐIỆN (A)<b> </span> </center> </td>  
          <td colspan="2"  align='left'> 
          
           <input id="dongdien" style="height:30px; width:240px" align="left" readonly> 
           </td> 
          </td>  
      </tr>
      
      <tr> 
         <td colspan="1" > <center> <span style = "color: Blue"> <b> CÔNG SUẤT (KWh)<b> </span> </center> </td>  
          <td colspan="2"  align='left'> 
          
           <input id="congsuat" style="height:30px; width:240px" align="left" readonly> 
           </td> 
          </td>  
      </tr>
        
          <tr> 
         <td colspan="1" > <center> <span style = "color: Blue"> <b> SỐ TIỀN (VND)<b> </span> </center> </td>  
          <td colspan="2"  align='left'> 
          
           <input id="sotien" style="height:30px; width:240px" align="left" readonly> 
           </td> 
          </td>  
        </tr>
        
          <tr> 
         <td colspan="1" > <center> <span style = "color: Blue"> <b> RELAY<b> </span> </center> </td>  
          <td colspan="2"  align='left'> 
          
            <center> <span id="RL"style = "color: Blue"> <b>ĐANG TẮT</b> </span> </center>
           </td> 
          </td>  
        </tr>
        
      
        
        
      
       
        
      
        
        
  
               
         </table>   


    </div>
    
    
    <div id="phongthemvaxoathe">
    
      <table width="800px" height="auto" border="2" cellpadding="10" align="center" >
              
        <tr  height="50"> 
            <td colspan="3" > <center> <span style = "color: Blue"> <b>THÊM VÀ XÓA THẺ</b> </span> </center> </td>  
           
        </tr>
        
        
         <tr> 
           <td colspan="1" > <center> <span style = "color: Blue"> <b> THÔNG BÁO</b> </span> </center> </td>  
            <td colspan="2"  align='left'> 
            
             <center> <span id="thongbaothemsuaxoa"style = "color: Blue"> <b>.....</b> </span> </center>
             </td> 
            </td>  
        </tr>
        
         <tr> 
           <td colspan="1" > <center> <span style = "color: Blue"> <b> MÃ THẺ</b> </span> </center> </td>  
            <td colspan="2"  align='left'> 
            
             <input id="mathethemsuaxoa" style="height:30px; width:240px" align="left" > 
             </td> 
            </td>  
        </tr>
        
          <tr> 
         <td colspan="1" > <center> <span style = "color: Blue"> <b> HỌ TÊN</b> </span> </center> </td>  
          <td colspan="2"  align='left'> 
          
           <input id="hotenthemsuaxoa" style="height:30px; width:240px" align="left"> 
           </td> 
          </td>  
        </tr>
        
        
         <tr> 
         <td colspan="1" > <center> <span style = "color: Blue"> <b> SỐ ĐIỆN THOẠI</b> </span> </center> </td>  
          <td colspan="2"  align='left'> 
          
           <input id="sdtthemsuaxoa" style="height:30px; width:240px" align="left"> 
           </td> 
          </td>  
        </tr>
        
          <tr> 
         <td colspan="1" > <center> <span style = "color: Blue"> <b> BIỂN SỐ XE</b> </span> </center> </td>  
          <td colspan="2"  align='left'> 
          
           <input id="biensoxethemsuaxoa" style="height:30px; width:240px" align="left"> 
           </td> 
          </td>  
        </tr>
        
            
      <tr> 
         <td colspan="1" > <center> <span style = "color: Blue"> <b> DÒNG ĐIỆN (A)<b> </span> </center> </td>  
          <td colspan="2"  align='left'> 
          
           <input id="dongdienthemsuaxoa" style="height:30px; width:240px" align="left" > 
           </td> 
          </td>  
      </tr>
      
      <tr> 
         <td colspan="1" > <center> <span style = "color: Blue"> <b> CÔNG SUẤT (KWh)<b> </span> </center> </td>  
          <td colspan="2"  align='left'> 
          
           <input id="congsuatthemsuaxoa" style="height:30px; width:240px" align="left" > 
           </td> 
          </td>  
      </tr>
        
          <tr> 
         <td colspan="1" > <center> <span style = "color: Blue"> <b> SỐ TIỀN (VND)<b> </span> </center> </td>  
          <td colspan="2"  align='left'> 
          
           <input id="sotienthemsuaxoa" style="height:30px; width:240px" align="left" > 
           </td> 
          </td>  
        </tr>
        
         <tr> 
         <td colspan="1" > <center> <span style = "color: Blue"> <b> CHỨC NĂNG<b> </span> </center> </td>  
          <td colspan="2"  align='left'> 
          
            <button class ="button" id= "btnthem" onclick = "BtnThem()">THÊM</button>
            <button class ="button" id= "btnsua" onclick = "BtnSua()">SỬA</button>
            <button class ="button" id= "btnxoa"  onclick = "BtnXoa()">XÓA</button>
            <button class ="button" onclick = "BtnReset()">RESET</button>
           </td> 
          </td>  
        </tr>
        
    
      </table>
    </div>
    
    
    <table width="800px" height="auto" border="2" cellpadding="10" align="center" >
              

        
        
         <tr> 
         
          <td colspan="2"  align='left'> 
          
              <button class ="button" onclick = "ThemXoaThe()">TÍNH NĂNG</button>
           </td> 
          </td>  
        </tr>
    
    </table>

      
  
   </body> 
   
  </html>



)rawliteral";
