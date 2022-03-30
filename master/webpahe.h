//=====================
//HTML code for webpage
//=====================
const char webpageCont[] PROGMEM = 
R"=====(
<!DOCTYPE HTML>
<html>
<title>ESP32 WebSocket Server</title>
<!---------------------------CSS-------------------------->
<style>
    #dynRectangle
    {
        width:0px;
        height:12px;
        top: 9px;
        background-color: red;
        z-index: -1;
        margin-top:8px;
    }
    body   {background-color:rgba(128,128,128,0.322); font-family:calibri}
    h1     {font-size: 40px; color: black; text-align: center}
    h2     {font-size: 30px; color: blue}
    h3     {font-size: 17px; color:blue}
    div.h1 {background-color: whitesmoke;}
</style>
<!--------------------------HTML-------------------------->
<body>
    <h1><div class="h1">ESP32 WebSocket Server</div></h1>
    <center>
    <h2>
        Board 1 Voltage: <span style="color:rgb(216, 3, 3)" id="board1V">0</span> V  
    </h2>
    <h2>
        Board 2 Voltage: <span style="color:rgb(216, 3, 3)" id="board2V">0</span> V  
    </h2>
    <h2>
        Board 3 Voltage: <span style="color:rgb(216, 3, 3)" id="board3V">0</span> V  
    </h2>    
    <center>
</body>
<!----------------------JavaScript------------------------>
<script>
  InitWebSocket()
  function InitWebSocket()
  {
    websock = new WebSocket('ws://'+window.location.hostname+':81/');
    websock.onmessage=function(evt)
    {
      
       JSONobj = JSON.parse(evt.data);
      
  document.getElementById('board1V').innerHTML = JSONobj.board1;
  document.getElementById('board2V').innerHTML = JSONobj.board2;
  document.getElementById('board3V').innerHTML = JSONobj.board3;


    }
  }
</script>
</html>
)=====";
