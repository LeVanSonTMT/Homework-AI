<?php
// đọc file Bai1.txt ra mảng $bienmang
    $bienmang = [];
    $myfile= fopen("bai1.txt",'r') or die("file không tồn tại!");
    while(!feof($myfile))
    {
        $temp = fgets($myfile);
        $bienmang[] = $temp;
    }
    fclose($myfile);

    $mangTieude = []; // chứa những Action thu được
    $mangKQ = []; // chứa những kết quả thu được
    $chay=1;
    $newMangMoi = []; // chứa những phần tử của $mang trong file.cpp 
    foreach ($bienmang as $key => $name){
        if($key != $chay){
            $mangTieude[] = $bienmang[$key];
        }
        if($key == $chay){
            $tmp = explode(',',$name); // tách chuỗi $name thành 1 mảng mới.
            foreach($tmp as $key1 => $value1){
                if($value1=='Ech_Vang'){
                    $newMangMoi[$key1]='<span class="sp"><img class="anh" src="2.png"></span>';
                }
                else if($value1=='Ech_Xanh'){
                    $newMangMoi[$key1]='<span class="sp"><img class="anh" src="1.png"></span>';
                }
                else if($value1=='0'){
                    $newMangMoi[$key1]='<span class="sp"><img class="anh" src="0.png"></span>';
                }
                else  $newMangMoi[$key1]=$value1;
            }
            $chay=$chay+2;
            $str = implode(" ", $newMangMoi); // gộp mảng $newMangMoi lại thành chuổi mới.
            $mangKQ[] =  $str;
        }
    }
    array_pop($mangTieude); // xóa phần tử cuối của $mangTieude;
?>

<html>
    <head>
        <meta charset="utf-8">
        <title>Bài toán đưa ếch qua ao</title>
        <style>
            body {
              background-color: lightgrey;
            }
            #noidung {
              width: 900px;
              margin: 0px auto;
              background-color: white;
              padding: 0px 0px;
            }
            #action
            {
                font-size: 25px;
                text-indent: 20px;
            }
            .anh
            {
                width: 82px;
                height: 110px;
                padding: 10px 0px 0px 0px;
                margin: 120px 0px 0px 0px;

            }
            .sp
            {
                width: 250px;
                height: 250px;
                margin: 10px 10px 0px 10px;
            }
            #div1
            {
                background-image: url("anhbia.png");
                width: 88%;
                height: 250px;
                margin: 0px auto;
            }
            #ip
            {
                text-align: center;
            }
            .inp
            {
                margin: 0px 0px 10px 0px;
                font-weight: bold;
                text-align: center;
                background-color: #C0C0C0;
            }
            .tieude {
              color: red;
              text-shadow: 2px 5px 5px yellow;
              font-size: 35px;
              font-weight: bold;
              text-align: center;
              padding: 10px 0px;
              margin: 0px 0px;
              border-top: solid black 2px;
              border-bottom: solid black 2px;
             }
             .debai{
               font-size: 20px;
               text-align: justify;
               width: 800px;
               margin: 0px auto;
               text-indent: 40px;
               padding-top: 5px;
             }
             #win
             {
              color: #CC9900;
              text-shadow: 2px 5px 5px yellow;
              font-size: 35px;
              font-weight: bold;
              text-align: center;
              padding: 10px 0px;
              margin: 0px 0px;
             }
        </style>
    </head>
    <body>
      <div id="noidung">
        <div class="gioithieu">
          <p class="tieude"> BÁO CÁO ĐỒ ÁN TRÍ TUỆ NHÂN TẠO </br> BÀI TOÁN ĐƯA ẾCH QUA AO</p>
        </div>
        <div class="debai">
            Đưa ếch qua ao là một trò chơi khá phổ biến rồi! Nhiệm vụ của bạn là đưa giúp tất cả
            ếch vàng sang bờ bên kia và ếch nâu sang bờ ngược lại. Biết rằng ếch chỉ nhảy được một
            bước và có thể nhảy qua đầu ếch khác màu nếu phía trước còn đá trống.
            Có 7 phiến đá, có 6 con ếch với 2 màu khác nhau được bố trí như bên dưới. Làm thế
            nào để 3 con ếch ở bờ bên đây có thể sang bờ bên kia và ngược lại. Biết rằng ếch chỉ nhảy
            được một bước và có thể nhảy qua đầu ếch khác màu nếu phía trước còn phiến đá trống.
        </div>
        <p class="debai"> Có <?php echo count($mangTieude)-1; ?> bước di chuyển con ếch để đạt được kết quả<p>
        <p id ="action"> <?php echo $mangTieude['0'] ?> </p>
        <div id ="div1"> <?php echo $mangKQ['0'] ?> </div>
        <p id="win"> </p>
        <div id="ip" >
        <input class="inp" type="button" name="restart" value="Restart" onclick="restart()">
        <input class="inp" type="button" name="previous" value="Previous" onclick="changeSlide(-1)">
		<input class="inp" type="button" name="next" value="Next" onclick="changeSlide(1)">
        </div>    
    <script>
        var i=0;
        var mangAction = <?php echo json_encode($mangTieude); ?>;
        var mangKQ = <?php echo json_encode($mangKQ); ?>;
            function restart()
            {
                i=0;
                document.getElementById('action').innerHTML = mangAction[i];
                document.getElementById('div1').innerHTML = mangKQ[i];
                document.getElementById('win').innerHTML = "";
            }
            function changeSlide(pos) 
            {
                //alert(i);
                if (pos == 1){
                    if(i<15){
                        i++;
                        document.getElementById('action').innerHTML = mangAction[i];
                        document.getElementById('div1').innerHTML = mangKQ[i];
                        
                    }
                }
                else {
                    if(i>0){
                        i--;
                        document.getElementById('action').innerHTML = mangAction[i];
                        document.getElementById('div1').innerHTML = mangKQ[i];
                    }
                }
                if(i==15) document.getElementById('win').innerHTML = "Hoàn Thành";
                else document.getElementById('win').innerHTML = "";
            }    

    </script>
</div>
<audio autoplay loop>
    <source src="nghenhac.mp3" type="audio/mpeg">
</audio>

    </body>
</html>
