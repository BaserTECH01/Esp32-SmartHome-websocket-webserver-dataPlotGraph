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

    body   {background-color:rgba(128,128,128,0.322); font-family:calibri}
    h1     {font-size: 40px; color: black; text-align: center}
    
    h3     {font-size: 17px; color:blue}
    div.h1 {background-color: whitesmoke;}

    table, th, td {
    border: 2px solid black;
    border-radius: 7px;
    
    }
    td{
        style="width:40%"
    }
    th, td{
        text-align: center;
        font-size: 300%
    }
    th{
        style="width:60%"
        
    }
    tr:nth-child(even) {
    background-color: #D6EEEE;
    }
    
        
    
</style>
<!--------------------------HTML-------------------------->
<body>
    <h1><div class="h1">ESP32 WebSocket Server</div></h1>
 <center> 
    <table style="width:100%" >
  <tr style="height:150px">
    <th>Boards</th>
    <th>Volts</th> 
    <th>Currents</th>
    <th>State</th>
  </tr>
  <tr style="height:100px">
    <td>Board 1</td>
    <td><span style="color:rgb(216, 3, 3)" id="board1V">0</span> V </td>
    <td><span style="color:rgb(15, 56, 245)" id="board1C">0</span> A</td>
    <td>ON</td>
  
  </tr>
  <tr style="height:100px">
    <td>Board 2</td>
    <td><span style="color:rgb(216, 3, 3)" id="board2V">0</span> V </td>
    <td><span style="color:rgb(15, 56, 245)" id="board2C">0</span> A</td>
    <th>ON</td>
  </tr>
  <tr style="height:100px">
    <td>Board 3</td>
    <td><span style="color:rgb(216, 3, 3)" id="board3V">0</span> V </td>
    <td><span style="color:rgb(15, 56, 245)" id="board3C">0</span> A</td>
    <th>ON</td>
  </tr>
  <tr style="height:100px">
    <td>Board 4</td>
    <td><span style="color:rgb(216, 3, 3)" id="board4V">0</span> V </td>
    <td><span style="color:rgb(15, 56, 245)" id="board4C">0</span> A</td>
    <th>ON</td>
  </tr>
  <tr style="height:100px">
    <td>Board 5</td>
    <td><span style="color:rgb(216, 3, 3)" id="board5V">0</span> V </td>
    <td><span style="color:rgb(15, 56, 245)" id="board5C">0</span> A</td>
    <th>ON</td>
  </tr>

  <tr style="height:100px">
    <td>Board 5</td>
    <td><span style="color:rgb(216, 3, 3)" id="board5V">0</span> V </td>
    <td><span style="color:rgb(15, 56, 245)" id="board5C">0</span> A</td>
    <th>ON</td>
  </tr>

  <tr style="height:100px">
    <td>Board 6</td>
    <td><span style="color:rgb(216, 3, 3)" id="board6V">0</span> V </td>
    <td><span style="color:rgb(15, 56, 245)" id="board6C">0</span> A</td>
    <th>ON</td>
  </tr>

  <tr style="height:100px">
    <td>Board 7</td>
    <td><span style="color:rgb(216, 3, 3)" id="board7V">0</span> V </td>
    <td><span style="color:rgb(15, 56, 245)" id="board7C">0</span> A</td>
    <th>ON</td>
  </tr>

  <tr style="height:100px">
    <td>Board 8</td>
    <td><span style="color:rgb(216, 3, 3)" id="board8V">0</span> V </td>
    <td><span style="color:rgb(15, 56, 245)" id="board8C">0</span> A</td>
    <th>ON</td>
  </tr>

  <tr style="height:100px">
    <td>Board 9</td>
    <td><span style="color:rgb(216, 3, 3)" id="board9V">0</span> V </td>
    <td><span style="color:rgb(15, 56, 245)" id="board9C">0</span> A</td>
    <th>ON</td>
  </tr>

  <tr style="height:100px">
    <td>Board 10</td>
    <td><span style="color:rgb(216, 3, 3)" id="board10V">0</span> V </td>
    <td><span style="color:rgb(15, 56, 245)" id="board10C">0</span> A</td>
    <th>ON</td>
  </tr>

  <tr style="height:100px">
    <td>Board 11</td>
    <td><span style="color:rgb(216, 3, 3)" id="board11V">0</span> V </td>
    <td><span style="color:rgb(15, 56, 245)" id="board11C">0</span> A</td>
    <th>ON</td>
  </tr>

  <tr style="height:100px">
    <td>Board 12</td>
    <td><span style="color:rgb(216, 3, 3)" id="board12V">0</span> V </td>
    <td><span style="color:rgb(15, 56, 245)" id="board12C">0</span> A</td>
    <th>ON</td>
  </tr>

  <tr style="height:100px">
    <td>Board 13</td>
    <td><span style="color:rgb(216, 3, 3)" id="board13V">0</span> V </td>
    <td><span style="color:rgb(15, 56, 245)" id="board13C">0</span> A</td>
    <th>ON</td>
  </tr>

  <tr style="height:100px">
    <td>Board 14</td>
    <td><span style="color:rgb(216, 3, 3)" id="board14V">0</span> V </td>
    <td><span style="color:rgb(15, 56, 245)" id="board14C">0</span> A</td>
    <th>ON</td>
  </tr>

  <tr style="height:100px">
    <td>Board 15</td>
    <td><span style="color:rgb(216, 3, 3)" id="board15V">0</span> V </td>
    <td><span style="color:rgb(15, 56, 245)" id="board15C">0</span> A</td>
    <th>ON</td>
  </tr>

  <tr style="height:100px">
    <td>Board 16</td>
    <td><span style="color:rgb(216, 3, 3)" id="board16V">0</span> V </td>
    <td><span style="color:rgb(15, 56, 245)" id="board16C">0</span> A</td>
    <th>ON</td>
  </tr>

  <tr style="height:100px">
    <td>Board 17</td>
    <td><span style="color:rgb(216, 3, 3)" id="board17V">0</span> V </td>
    <td><span style="color:rgb(15, 56, 245)" id="board17C">0</span> A</td>
    <th>ON</td>
  </tr>

  <tr style="height:100px">
    <td>Board 18</td>
    <td><span style="color:rgb(216, 3, 3)" id="board18V">0</span> V </td>
    <td><span style="color:rgb(15, 56, 245)" id="board18C">0</span> A</td>
    <th>ON</td>
  </tr>

  <tr style="height:100px">
    <td>Board 19</td>
    <td><span style="color:rgb(216, 3, 3)" id="board19V">0</span> V </td>
    <td><span style="color:rgb(15, 56, 245)" id="board19C">0</span> A</td>
    <th>ON</td>
  </tr>

  <tr style="height:100px">
    <td>Board 20</td>
    <td><span style="color:rgb(216, 3, 3)" id="board20V">0</span> V </td>
    <td><span style="color:rgb(15, 56, 245)" id="board20C">0</span> A</td>
    <th>ON</td>
  </tr>
      
 </table>
 </center>
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
      
  document.getElementById('board1V').innerHTML = JSONobj.brd1V;
  document.getElementById('board1C').innerHTML = JSONobj.brd1C;
  document.getElementById('board2V').innerHTML = JSONobj.brd2V;
  document.getElementById('board2C').innerHTML = JSONobj.brd2C;
  document.getElementById('board3V').innerHTML = JSONobj.brd3V;
  document.getElementById('board3C').innerHTML = JSONobj.brd3C;



    }
  }
</script>
</html>
)=====";
