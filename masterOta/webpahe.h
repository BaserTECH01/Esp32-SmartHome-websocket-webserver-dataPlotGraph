//=====================
//HTML code for webpage
//=====================
const char webpageCont[] PROGMEM = 
R"=====(
<!DOCTYPE HTML>
<html>
<title>ESP32 WebSocket Server</title>
<head>
  <script src='https://cdnjs.cloudflare.com/ajax/libs/Chart.js/2.5.0/Chart.min.js'></script>
</head>


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
        font-size: 150%
    }
    th{
        style="width:60%"
        
    }
    tr:nth-child(even) {
     background-color: #D6EEEE;
    }
    

    .button {
      padding: 15px 25px;
      font-size: 20px;
      text-align: center;
      cursor: pointer;
      outline: none;
      color: #fff;
      background-color: #04AA6D;
      border: none;
      border-radius: 15px;
      box-shadow: 0 9px #999;
    }

    .button:hover {background-color: #3e8e41}

    .button:active {
     background-color: #3e8e41;
     box-shadow: 0 5px #666;
     transform: translateY(4px);
    }

    .buttonMinik {
      padding: 9px 9px;
      font-size: 12px;
      text-align: center;
      cursor: pointer;
      outline: none;
      color: #fff;
      background-color: #04AA6D;
      border: none;
      border-radius: 7px;
      box-shadow: 0 4px #999;
    }

    .buttonMinik:hover {background-color: #3e8e41}

    .buttonMinik:active {
     background-color: #3e8e41;
     box-shadow: 0 3px #666;
     transform: translateY(3px);
    }

    input {
     width:40%;
     height:10%;
   }


canvas {
  border: 3px outset red;
  background-color: lightblue;
  border-radius: 7px; 
}

.chart-container {
  margin:5%;
  display: flex;
  flex-wrap: nowrap;
  width: 45%;
  
}

</style>
<!--------------------------HTML-------------------------->
<body onload="javascript:solar()">
<h1><div class="h1">Smart Home Dashboard</div></h1>

    <div>
 <center>
 <a href="http://10.60.1.43/serverIndex" target="_blank" rel="noopener noreferrer">
 <button class="button" style="background-color:rgb(3, 30, 223)" >Update for firmware of master</button>
 </a>
 <p></p>
<br>
</div>



 <div >
 <a style=rgba(128,128,128,0.322) ></a>
 </div>
 </center>
 


<div class="chart-container">

    <canvas id="line-chart" ></canvas>  
  <p style="color:rgba(214,214,214,255)" >a</p>
    <canvas id="chart_solar" ></canvas> 
  
</div>

    <table style="width:100%" >
  <tr style="height:50px">
    <th>Boards</th>
    <th>Watts</th> 
    <th>Currents</th>
    <th>State</th>
    <th>Mode</th>
    <th>Timer</th>

  </tr>
  
  <tr style="height:100px">
    <td><p>board 1</p><p style="color:red;" id="brd1connectStatus" >Connection</p></td>
    <td><span style="color:rgb(216, 3, 3)" id="board1V">0</span> W </td>
    <td><span style="color:rgb(15, 56, 245)" id="board1C">0</span> A</td>
    <th><button class="button"  id="btn"  onclick="button()" > </button></td>
    <th><button class="button"  id="Mbtn1"  onclick="Mod1()" ></button></td>
    <th>     <select disabled="true" id="brd1timerNo" required>
               <option value="" selected disabled>Timer interval no</option>
               <option value="1">1</option>
               <option value="2">2</option>
               <option value="3">3</option>
             </select>
             <br>
         <input type ="time" disabled="true" id="brd1BasS1" min="0" max="23" placeholder="Start Hour"></input><br>
         <input type ="time" disabled="true" id="brd1BasD1" min="0" max="59" placeholder="Start Min"></input><br>
         <input type ="time" disabled="true" id="brd1SonS1" min="0" max="23" placeholder="End Hour"></input><br>
         <input type ="time" disabled="true" id="brd1SonD1" min="0" max="59" placeholder="End Min"></input><br>
        <button class="buttonMinik" onclick="sendinput()">send</button><br><br>
        
    </td>  
  </tr> 
  
  <tr style="height:100px">
    <td><p>board 2</p><p style="color:red;" id="brd2connectStatus" >Connection</p></td>
    <td><span style="color:rgb(216, 3, 3)" id="board2V">0</span> W </td>
    <td><span style="color:rgb(15, 56, 245)" id="board2C">0</span> A</td>
    <th><button class="button"  id="btn2"  onclick="button2()" > </button></td>
    <th><button class="button"  id="Mbtn2"  onclick="Mod2()" ></button></td>
    <th>     <select disabled="true" id="brd2timerNo" required>
               <option value="" selected disabled>Timer interval no</option>
               <option value="1">1</option>
               <option value="2">2</option>
               <option value="3">3</option>
             </select>
             <br>    
        <input type ="time" disabled="true" id="brd2BasS1" min="0" max="23" placeholder="Start Hour"></input><br>
        <input type ="time" disabled="true" id="brd2BasD1" min="0" max="59" placeholder="Start Min"></input><br>
        <input type ="time" disabled="true" id="brd2SonS1" min="0" max="23" placeholder="End Hour"></input><br>
        <input type ="time" disabled="true" id="brd2SonD1" min="0" max="59" placeholder="End Min"></input><br>
        <button class="buttonMinik" onclick="brd2time()">send</button><br><br>
    </td>  
  </tr>
  
  <tr style="height:100px">
    <td><p>board 3</p><p style="color:red;" id="brd3connectStatus" >Connection</p></td>
    <td><span style="color:rgb(216, 3, 3)" id="board3V">0</span> W </td>
    <td><span style="color:rgb(15, 56, 245)" id="board3C">0</span> A</td>
    <th><button class="button"  id="btn3"  onclick="button3()" > </button></td>
    <th><button class="button"  id="Mbtn3"  onclick="Mod3()" ></button></td>
    <th>     <select disabled="true" id="brd3timerNo" required>
               <option value="" selected disabled>Timer interval no</option>
               <option value="1">1</option>
               <option value="2">2</option>
               <option value="3">3</option>
             </select>
             <br>
         <input type ="time" disabled="true" id="brd3BasS1" min="0" max="23" placeholder="Start Hour"></input><br>
         <input type ="time" disabled="true" id="brd3BasD1" min="0" max="59" placeholder="Start Min"></input><br>
         <input type ="time" disabled="true" id="brd3SonS1" min="0" max="23" placeholder="End Hour"></input><br>
         <input type ="time" disabled="true" id="brd3SonD1" min="0" max="59" placeholder="End Min"></input><br>
        <button class="buttonMinik" onclick="brd3time()">send</button><br><br>
        
    </td>
  </tr>
  
  <tr style="height:100px">
    <td><p>board 4</p><p style="color:red;" id="brd4connectStatus" >Connection</p></td>
    <td><span style="color:rgb(216, 3, 3)" id="board4V">0</span> W </td>
    <td><span style="color:rgb(15, 56, 245)" id="board4C">0</span> A</td>
    <th><button class="button"  id="btn4"  onclick="button4()" > </button></td>
    <th><button class="button"  id="Mbtn4"  onclick="Mod4()" ></button></td>
    <th>     <select disabled="true" id="brd4timerNo" required>
               <option value="" selected disabled>Timer interval no</option>
               <option value="1">1</option>
               <option value="2">2</option>
               <option value="3">3</option>
             </select>
             <br>
         <input type ="time" disabled="true" id="brd4BasS1" min="0" max="23" placeholder="Start Hour"></input><br>
         <input type ="time" disabled="true" id="brd4BasD1" min="0" max="59" placeholder="Start Min"></input><br>
         <input type ="time" disabled="true" id="brd4SonS1" min="0" max="23" placeholder="End Hour"></input><br>
         <input type ="time" disabled="true" id="brd4SonD1" min="0" max="59" placeholder="End Min"></input><br>
        <button class="buttonMinik" onclick="brd4time()">send</button><br><br>
        
    </td>
  </tr>
  
  <tr style="height:100px">
    <td><p>board 5</p><p style="color:red;" id="brd5connectStatus" >Connection</p></td>
    <td><span style="color:rgb(216, 3, 3)" id="board5V">0</span> W </td>
    <td><span style="color:rgb(15, 56, 245)" id="board5C">0</span> A</td>
    <th><button class="button"  id="btn5"  onclick="button5()" > </button></td>
    <th><button class="button"  id="Mbtn5"  onclick="Mod5()" ></button></td>
    <th>     <select disabled="true" id="brd5timerNo" required>
               <option value="" selected disabled>Timer interval no</option>
               <option value="1">1</option>
               <option value="2">2</option>
               <option value="3">3</option>
             </select>
             <br>
         <input type ="time" disabled="true" id="brd5BasS1" min="0" max="23" placeholder="Start Hour"></input><br>
         <input type ="time" disabled="true" id="brd5BasD1" min="0" max="59" placeholder="Start Min"></input><br>
         <input type ="time" disabled="true" id="brd5SonS1" min="0" max="23" placeholder="End Hour"></input><br>
         <input type ="time" disabled="true" id="brd5SonD1" min="0" max="59" placeholder="End Min"></input><br>
        <button class="buttonMinik" onclick="brd5time()">send</button><br><br>
        
    </td>
  </tr>

  <tr style="height:100px">
    <td><p>board 6</p><p style="color:red;" id="brd6connectStatus" >Connection</p></td>
    <td><span style="color:rgb(216, 3, 3)" id="board6V">0</span> W </td>
    <td><span style="color:rgb(15, 56, 245)" id="board6C">0</span> A</td>
    <th><button class="button"  id="btn6"  onclick="button6()" > </button></td>
    <th><button class="button"  id="Mbtn6"  onclick="Mod6()" ></button></td>
    <th>     <select disabled="true" id="brd6timerNo" required>
               <option value="" selected disabled>Timer interval no</option>
               <option value="1">1</option>
               <option value="2">2</option>
               <option value="3">3</option>
             </select>
             <br>
         <input type ="time" disabled="true" id="brd6BasS1" min="0" max="23" placeholder="Start Hour"></input><br>
         <input type ="time" disabled="true" id="brd6BasD1" min="0" max="59" placeholder="Start Min"></input><br>
         <input type ="time" disabled="true" id="brd6SonS1" min="0" max="23" placeholder="End Hour"></input><br>
         <input type ="time" disabled="true" id="brd6SonD1" min="0" max="59" placeholder="End Min"></input><br>
        <button class="buttonMinik" onclick="brd6time()">send</button><br><br>
        
    </td>
  </tr>

  <tr style="height:100px">
    <td><p>board 7</p><p style="color:red;" id="brd7connectStatus" >Connection</p></td>
    <td><span style="color:rgb(216, 3, 3)" id="board7V">0</span> W </td>
    <td><span style="color:rgb(15, 56, 245)" id="board7C">0</span> A</td>
    <th><button class="button"  id="btn7"  onclick="button7()" > </button></td>
    <th><button class="button"  id="Mbtn7"  onclick="Mod7()" ></button></td>
    <th>     <select disabled="true" id="brd7timerNo" required>
               <option value="" selected disabled>Timer interval no</option>
               <option value="1">1</option>
               <option value="2">2</option>
               <option value="3">3</option>
             </select>
             <br>
         <input type ="time" disabled="true" id="brd7BasS1" min="0" max="23" placeholder="Start Hour"></input><br>
         <input type ="time" disabled="true" id="brd7BasD1" min="0" max="59" placeholder="Start Min"></input><br>
         <input type ="time" disabled="true" id="brd7SonS1" min="0" max="23" placeholder="End Hour"></input><br>
         <input type ="time" disabled="true" id="brd7SonD1" min="0" max="59" placeholder="End Min"></input><br>
        <button class="buttonMinik" onclick="brd7time()">send</button><br><br>
        
    </td>
  </tr>


  <tr style="height:100px">
    <td><p>board 8</p><p style="color:red;" id="brd8connectStatus" >Connection</p></td>
    <td><span style="color:rgb(216, 3, 3)" id="board8V">0</span> W </td>
    <td><span style="color:rgb(15, 56, 245)" id="board8C">0</span> A</td>
    <th><button class="button"  id="btn8"  onclick="button8()" > </button></td>
    <th><button class="button"  id="Mbtn8"  onclick="Mod8()" ></button></td>
    <th>     <select disabled="true" id="brd8timerNo" required>
               <option value="" selected disabled>Timer interval no</option>
               <option value="1">1</option>
               <option value="2">2</option>
               <option value="3">3</option>
             </select>
             <br>
         <input type ="time" disabled="true" id="brd8BasS1" min="0" max="23" placeholder="Start Hour"></input><br>
         <input type ="time" disabled="true" id="brd8BasD1" min="0" max="59" placeholder="Start Min"></input><br>
         <input type ="time" disabled="true" id="brd8SonS1" min="0" max="23" placeholder="End Hour"></input><br>
         <input type ="time" disabled="true" id="brd8SonD1" min="0" max="59" placeholder="End Min"></input><br>
        <button class="buttonMinik" onclick="brd8time()">send</button><br><br>
        
    </td>
  </tr>

<tr style="height:100px">
    <td><p>board 9</p><p style="color:red;" id="brd9connectStatus" >Connection</p></td>
    <td><span style="color:rgb(216, 3, 3)" id="board9V">0</span> W </td>
    <td><span style="color:rgb(15, 56, 245)" id="board9C">0</span> A</td>
    <th><button class="button"  id="btn9"  onclick="button9()" > </button></td>
    <th><button class="button"  id="Mbtn9"  onclick="Mod9()" ></button></td>
    <th>     <select disabled="true" id="brd9timerNo" required>
               <option value="" selected disabled>Timer interval no</option>
               <option value="1">1</option>
               <option value="2">2</option>
               <option value="3">3</option>
             </select>
             <br>
         <input type ="time" disabled="true" id="brd9BasS1" min="0" max="23" placeholder="Start Hour"></input><br>
         <input type ="time" disabled="true" id="brd9BasD1" min="0" max="59" placeholder="Start Min"></input><br>
         <input type ="time" disabled="true" id="brd9SonS1" min="0" max="23" placeholder="End Hour"></input><br>
         <input type ="time" disabled="true" id="brd9SonD1" min="0" max="59" placeholder="End Min"></input><br>
        <button class="buttonMinik" onclick="brd9time()">send</button><br><br>
        
    </td>
  </tr>

<tr style="height:100px">
    <td><p>board 10</p><p style="color:red;" id="brd10connectStatus" >Connection</p></td>
    <td><span style="color:rgb(216, 3, 3)" id="board10V">0</span> W </td>
    <td><span style="color:rgb(15, 56, 245)" id="board10C">0</span> A</td>
    <th><button class="button"  id="btn10"  onclick="button10()" > </button></td>
    <th><button class="button"  id="Mbtn10"  onclick="Mod10()" ></button></td>
    <th>     <select disabled="true" id="brd10timerNo" required>
               <option value="" selected disabled>Timer interval no</option>
               <option value="1">1</option>
               <option value="2">2</option>
               <option value="3">3</option>
             </select>
             <br>
         <input type ="time" disabled="true" id="brd10BasS1" min="0" max="23" placeholder="Start Hour"></input><br>
         <input type ="time" disabled="true" id="brd10BasD1" min="0" max="59" placeholder="Start Min"></input><br>
         <input type ="time" disabled="true" id="brd10SonS1" min="0" max="23" placeholder="End Hour"></input><br>
         <input type ="time" disabled="true" id="brd10SonD1" min="0" max="59" placeholder="End Min"></input><br>
        <button class="buttonMinik" onclick="brd10time()">send</button><br><br>
        
    </td>
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
 
</body>
<!----------------------JavaScript------------------------>
<script> 
  var dataPlot;
  var dataPlot2;
  var maxDataPoints = 20;
  function removeData(){
    dataPlot.data.labels.shift();
    dataPlot.data.datasets[0].data.shift();
    dataPlot.data.datasets[1].data.shift();
    dataPlot.data.datasets[2].data.shift();
    dataPlot.data.datasets[3].data.shift();
    dataPlot.data.datasets[4].data.shift();
    dataPlot.data.datasets[5].data.shift();
    dataPlot.data.datasets[6].data.shift();
    dataPlot.data.datasets[7].data.shift();
    dataPlot.data.datasets[8].data.shift();
    dataPlot.data.datasets[9].data.shift();
  }
  function addData(label, data) {
    if(dataPlot.data.labels.length > maxDataPoints) removeData(); 
    dataPlot.data.datasets[0].data.push(data);
    dataPlot.update();
  }
  function addData2(label, data) {
    dataPlot.data.labels.push(label);
    dataPlot.data.datasets[1].data.push(data);
    dataPlot.update();
  }

  function addData3(label, data) {
    dataPlot.data.datasets[2].data.push(data);
    dataPlot.update();
  }

  function addData4(label, data) {
    dataPlot.data.datasets[3].data.push(data);
    dataPlot.update();
  }      

  function addData5(label, data) {
    dataPlot.data.datasets[4].data.push(data);
    dataPlot.update();
  }   

  function addData6(label, data) {
    dataPlot.data.datasets[5].data.push(data);
    dataPlot.update();
  }
  
  function addData7(label, data) {
    dataPlot.data.datasets[6].data.push(data);
    dataPlot.update();
  }
  
  function addData8(label, data) {
    dataPlot.data.datasets[7].data.push(data);
    dataPlot.update();
  } 

  function addData9(label, data) {
    dataPlot.data.datasets[8].data.push(data);
    dataPlot.update();
  } 

  function addData10(label, data) {
    dataPlot.data.datasets[9].data.push(data);
    dataPlot.update();
  }   
  function solar()
     {
        
       dataPlot2 = new Chart(document.getElementById("chart_solar"), {
       type: 'line',
        data: {
          labels: [1,2,3,4,5,6,7,8,9,10],
          datasets: [{
          data: [10,20,120,50,80,60,50,40,30,90],
          label: "Solar panel Power",
          borderColor: "red",
          fill: false
            }]
        }
          });
        dataPlot2.data.datasets[0].data.push(data);       
        dataPlot2.update();

       } 

    

  
  InitWebSocket()
  function InitWebSocket()
  {
    websock = new WebSocket('ws://'+window.location.hostname+':81/');
    
      dataPlot = new Chart(document.getElementById("line-chart"), {
      type: 'line',
      data: {
        labels: [],
        datasets: [{
          data: [],
          label: "Board 1 Current (A)",
          borderColor: "red",
          fill: false
        },
        {
          data: [1],
          label: "Board 2 Current (A)",
          borderColor: "blue",
          fill: false
        },
        {
          data: [2],
          label: "Board 3 Current (A)",
          borderColor: "green",
          fill: false
        },
        {
          data: [3],
          label: "Board 4 Current (A)",
          borderColor: "#00ff00",
          fill: false                
        },
        {
          data: [4],
          label: "Board 5 Current (A)",
          borderColor: "#A3E4D7",
          fill: false                
        },
        {
          data: [5],
          label: "Board 6 Current (A)",
          borderColor: "#7D6608",
          fill: false                
        },
        {
          data: [6],
          label: "Board 7 Current (A)",
          borderColor: "#7D6608",
          fill: false                
        },
        {
          data: [7],
          label: "Board 8 Current (A)",
          borderColor: "#7D6608",
          fill: false                
        },
        {
          data: [8],
          label: "Board 9 Current (A)",
          borderColor: "yellow",
          fill: false                
        },
        {
          data: [9],
          label: "Board 10 Current (A)",
          borderColor: "6600cc",
          fill: false                
        }                         
        ]
      }
    });
    websock.onmessage=function(evt)
    {
      
      JSONobj = JSON.parse(evt.data);

      
//----------------Board---1-------------------------

      
        if(JSONobj.brd1V){


    
          addData(t, JSONobj.brd1C); 
      
          //1. BUTON
          if(JSONobj.brd1S == 'ON')
          {
            document.getElementById('btn').innerHTML = JSONobj.brd1S;
            document.getElementById('btn').style.background = '#3e8e41';
          }
          else if(JSONobj.brd1S == 'OFF')
          {
            document.getElementById('btn').innerHTML = JSONobj.brd1S;
            document.getElementById('btn').style.background='#d40505';
          }

          
          
          document.getElementById('board1V').innerHTML = JSONobj.brd1V;
          document.getElementById('board1C').innerHTML = JSONobj.brd1C;
          
          if(JSONobj.brd1M=='Manuel'){
          document.getElementById("btn").disabled = false;
          document.getElementById("brd1timerNo").disabled = true;
          document.getElementById("brd1BasS1").disabled = true;
          document.getElementById("brd1BasD1").disabled = true;
          document.getElementById("brd1SonS1").disabled = true;
          document.getElementById("brd1SonD1").disabled = true;
                
          document.getElementById('Mbtn1').innerHTML = JSONobj.brd1M;
          document.getElementById('Mbtn1').style.background = 'blue';
          }
          
          if(JSONobj.brd1M=='Timer'){
            document.getElementById("btn").disabled = true;
            document.getElementById("brd1timerNo").disabled = false;
            document.getElementById("brd1BasS1").disabled = false;
            document.getElementById("brd1BasD1").disabled = false;
            document.getElementById("brd1SonS1").disabled = false;
            document.getElementById("brd1SonD1").disabled = false;
                        
            document.getElementById('Mbtn1').innerHTML = JSONobj.brd1M;
            document.getElementById('Mbtn1').style.background = 'green';
          }



          if(JSONobj.brd1ConnectSt == 'Connected')
          {
            document.getElementById('brd1connectStatus').innerHTML = JSONobj.brd1ConnectSt;
            document.getElementById('brd1connectStatus').style.color = '#3e8e41';
          }

           if(JSONobj.brd1ConnectSt == 'No Connection')
          {
            document.getElementById('brd1connectStatus').innerHTML = JSONobj.brd1ConnectSt;
            document.getElementById('brd1connectStatus').style.color = '#d40505';
          }
          
        }

        //----------------Board---2-------------------------
          if(JSONobj.brd2V)
          {
      var today = new Date();
      var t = today.getHours() + ":" + today.getMinutes() + ":" + today.getSeconds();

      addData2(t, JSONobj.brd2C);
            
            //2. BUTON
            if(JSONobj.brd2S == 'ON')
            {
              document.getElementById('btn2').innerHTML = JSONobj.brd2S;
              document.getElementById('btn2').style.background = '#3e8e41';
             }
             else if(JSONobj.brd2S == 'OFF')
             {
              document.getElementById('btn2').innerHTML = JSONobj.brd2S;
              document.getElementById('btn2').style.background='#d40505';
             }

          
           document.getElementById('board2V').innerHTML = JSONobj.brd2V;
           document.getElementById('board2C').innerHTML = JSONobj.brd2C;

           if(JSONobj.brd2M=='Manuel'){
          document.getElementById("btn2").disabled = false;
          document.getElementById("brd2timerNo").disabled = true;
          document.getElementById("brd2BasS1").disabled = true;
          document.getElementById("brd2BasD1").disabled = true;
          document.getElementById("brd2SonS1").disabled = true;
          document.getElementById("brd2SonD1").disabled = true;
                
          document.getElementById('Mbtn2').innerHTML = JSONobj.brd2M;
          document.getElementById('Mbtn2').style.background = 'blue';            
           }

          if(JSONobj.brd2M=='Timer'){
            document.getElementById("btn2").disabled = true;
            document.getElementById("brd2timerNo").disabled = false;
            document.getElementById("brd2BasS1").disabled = false;
            document.getElementById("brd2BasD1").disabled = false;
            document.getElementById("brd2SonS1").disabled = false;
            document.getElementById("brd2SonD1").disabled = false;
                        
            document.getElementById('Mbtn2').innerHTML = JSONobj.brd2M;
            document.getElementById('Mbtn2').style.background = 'green';
          }
           
           if(JSONobj.brd2ConnectSt == 'Connected')
          {
            document.getElementById('brd2connectStatus').innerHTML = JSONobj.brd2ConnectSt;
            document.getElementById('brd2connectStatus').style.color = '#3e8e41';
          }

           if(JSONobj.brd2ConnectSt == 'No Connection')
          {
            document.getElementById('brd2connectStatus').innerHTML = JSONobj.brd2ConnectSt;
            document.getElementById('brd2connectStatus').style.color = '#d40505';
          }

          }


          //---------------Board--3-----------

          if(JSONobj.brd3V)
          {

      addData3(t, JSONobj.brd3C);

                  
            //3. BUTON
            if(JSONobj.brd3S == 'ON')
            {
              document.getElementById('btn3').innerHTML = JSONobj.brd3S;
              document.getElementById('btn3').style.background = '#3e8e41';
             }
             else if(JSONobj.brd3S == 'OFF')
             {
              document.getElementById('btn3').innerHTML = JSONobj.brd3S;
              document.getElementById('btn3').style.background='#d40505';
             }

          
           document.getElementById('board3V').innerHTML = JSONobj.brd3V;
           document.getElementById('board3C').innerHTML = JSONobj.brd3C;

           if(JSONobj.brd3M=='Manuel'){
          document.getElementById("btn3").disabled = false;
          document.getElementById("brd3timerNo").disabled = true;
          document.getElementById("brd3BasS1").disabled = true;
          document.getElementById("brd3BasD1").disabled = true;
          document.getElementById("brd3SonS1").disabled = true;
          document.getElementById("brd3SonD1").disabled = true;
                
          document.getElementById('Mbtn3').innerHTML = JSONobj.brd3M;
          document.getElementById('Mbtn3').style.background = 'blue';            
           }

          if(JSONobj.brd3M=='Timer'){
            document.getElementById("btn3").disabled = true;
            document.getElementById("brd3timerNo").disabled = false;
            document.getElementById("brd3BasS1").disabled = false;
            document.getElementById("brd3BasD1").disabled = false;
            document.getElementById("brd3SonS1").disabled = false;
            document.getElementById("brd3SonD1").disabled = false;
                        
            document.getElementById('Mbtn3').innerHTML = JSONobj.brd3M;
            document.getElementById('Mbtn3').style.background = 'green';
          }
           
           if(JSONobj.brd3ConnectSt == 'Connected')
          {
            document.getElementById('brd3connectStatus').innerHTML = JSONobj.brd3ConnectSt;
            document.getElementById('brd3connectStatus').style.color = '#3e8e41';
          }

           if(JSONobj.brd3ConnectSt == 'No Connection')
          {
            document.getElementById('brd3connectStatus').innerHTML = JSONobj.brd3ConnectSt;
            document.getElementById('brd3connectStatus').style.color = '#d40505';
          }

          }


          //---------------Board--4-----------

          if(JSONobj.brd4V)
          {

      addData4(t, JSONobj.brd4C);

                  
            //3. BUTON
            if(JSONobj.brd4S == 'ON')
            {
              document.getElementById('btn4').innerHTML = JSONobj.brd4S;
              document.getElementById('btn4').style.background = '#3e8e41';
             }
             else if(JSONobj.brd4S == 'OFF')
             {
              document.getElementById('btn4').innerHTML = JSONobj.brd4S;
              document.getElementById('btn4').style.background='#d40505';
             }

          
           document.getElementById('board4V').innerHTML = JSONobj.brd4V;
           document.getElementById('board4C').innerHTML = JSONobj.brd4C;

           if(JSONobj.brd4M=='Manuel'){
          document.getElementById("btn4").disabled = false;
          document.getElementById("brd4timerNo").disabled = true;
          document.getElementById("brd4BasS1").disabled = true;
          document.getElementById("brd4BasD1").disabled = true;
          document.getElementById("brd4SonS1").disabled = true;
          document.getElementById("brd4SonD1").disabled = true;
                
          document.getElementById('Mbtn4').innerHTML = JSONobj.brd4M;
          document.getElementById('Mbtn4').style.background = 'blue';            
           }

          if(JSONobj.brd4M=='Timer'){
            document.getElementById("btn4").disabled = true;
            document.getElementById("brd4timerNo").disabled = false;
            document.getElementById("brd4BasS1").disabled = false;
            document.getElementById("brd4BasD1").disabled = false;
            document.getElementById("brd4SonS1").disabled = false;
            document.getElementById("brd4SonD1").disabled = false;
                        
            document.getElementById('Mbtn4').innerHTML = JSONobj.brd4M;
            document.getElementById('Mbtn4').style.background = 'green';
          }
           
           if(JSONobj.brd4ConnectSt == 'Connected')
          {
            document.getElementById('brd4connectStatus').innerHTML = JSONobj.brd4ConnectSt;
            document.getElementById('brd4connectStatus').style.color = '#3e8e41';
          }

           if(JSONobj.brd4ConnectSt == 'No Connection')
          {
            document.getElementById('brd4connectStatus').innerHTML = JSONobj.brd4ConnectSt;
            document.getElementById('brd4connectStatus').style.color = '#d40505';
          }

          }       




       
          //---------------Board--5-----------

          if(JSONobj.brd5V)
          {

      addData5(t, JSONobj.brd5C);

                  
            //5. BUTON
            if(JSONobj.brd5S == 'ON')
            {
              document.getElementById('btn5').innerHTML = JSONobj.brd5S;
              document.getElementById('btn5').style.background = '#3e8e41';
             }
             else if(JSONobj.brd5S == 'OFF')
             {
              document.getElementById('btn5').innerHTML = JSONobj.brd5S;
              document.getElementById('btn5').style.background='#d40505';
             }

          
           document.getElementById('board5V').innerHTML = JSONobj.brd5V;
           document.getElementById('board5C').innerHTML = JSONobj.brd5C;

           if(JSONobj.brd5M=='Manuel'){
          document.getElementById("btn5").disabled = false;
          document.getElementById("brd5timerNo").disabled = true;
          document.getElementById("brd5BasS1").disabled = true;
          document.getElementById("brd5BasD1").disabled = true;
          document.getElementById("brd5SonS1").disabled = true;
          document.getElementById("brd5SonD1").disabled = true;
                
          document.getElementById('Mbtn5').innerHTML = JSONobj.brd5M;
          document.getElementById('Mbtn5').style.background = 'blue';            
           }

          if(JSONobj.brd5M=='Timer'){
            document.getElementById("btn5").disabled = true;
            document.getElementById("brd5timerNo").disabled = false;
            document.getElementById("brd5BasS1").disabled = false;
            document.getElementById("brd5BasD1").disabled = false;
            document.getElementById("brd5SonS1").disabled = false;
            document.getElementById("brd5SonD1").disabled = false;
                        
            document.getElementById('Mbtn5').innerHTML = JSONobj.brd5M;
            document.getElementById('Mbtn5').style.background = 'green';
          }
           
           if(JSONobj.brd5ConnectSt == 'Connected')
          {
            document.getElementById('brd5connectStatus').innerHTML = JSONobj.brd5ConnectSt;
            document.getElementById('brd5connectStatus').style.color = '#3e8e41';
          }

           if(JSONobj.brd5ConnectSt == 'No Connection')
          {
            document.getElementById('brd5connectStatus').innerHTML = JSONobj.brd5ConnectSt;
            document.getElementById('brd5connectStatus').style.color = '#d40505';
          }

          } 

          //---------------Board--6-----------

          if(JSONobj.brd6V)
          {

      addData6(t, JSONobj.brd6C);

                  
            //6. BUTON
            if(JSONobj.brd6S == 'ON')
            {
              document.getElementById('btn6').innerHTML = JSONobj.brd6S;
              document.getElementById('btn6').style.background = '#3e8e41';
             }
             else if(JSONobj.brd6S == 'OFF')
             {
              document.getElementById('btn6').innerHTML = JSONobj.brd6S;
              document.getElementById('btn6').style.background='#d40505';
             }

          
           document.getElementById('board6V').innerHTML = JSONobj.brd6V;
           document.getElementById('board6C').innerHTML = JSONobj.brd6C;

           if(JSONobj.brd6M=='Manuel'){
          document.getElementById("btn6").disabled = false;
          document.getElementById("brd6timerNo").disabled = true;
          document.getElementById("brd6BasS1").disabled = true;
          document.getElementById("brd6BasD1").disabled = true;
          document.getElementById("brd6SonS1").disabled = true;
          document.getElementById("brd6SonD1").disabled = true;
                
          document.getElementById('Mbtn6').innerHTML = JSONobj.brd6M;
          document.getElementById('Mbtn6').style.background = 'blue';            
           }

          if(JSONobj.brd6M=='Timer'){
            document.getElementById("btn6").disabled = true;
            document.getElementById("brd6timerNo").disabled = false;
            document.getElementById("brd6BasS1").disabled = false;
            document.getElementById("brd6BasD1").disabled = false;
            document.getElementById("brd6SonS1").disabled = false;
            document.getElementById("brd6SonD1").disabled = false;
                        
            document.getElementById('Mbtn6').innerHTML = JSONobj.brd6M;
            document.getElementById('Mbtn6').style.background = 'green';
          }
           
           if(JSONobj.brd6ConnectSt == 'Connected')
          {
            document.getElementById('brd6connectStatus').innerHTML = JSONobj.brd6ConnectSt;
            document.getElementById('brd6connectStatus').style.color = '#3e8e41';
          }

           if(JSONobj.brd6ConnectSt == 'No Connection')
          {
            document.getElementById('brd6connectStatus').innerHTML = JSONobj.brd6ConnectSt;
            document.getElementById('brd6connectStatus').style.color = '#d40505';
          }

          }


          //---------------Board--7-----------

          if(JSONobj.brd7V)
          {

      addData7(t, JSONobj.brd7C);

                  
            //7. BUTON
            if(JSONobj.brd7S == 'ON')
            {
              document.getElementById('btn7').innerHTML = JSONobj.brd7S;
              document.getElementById('btn7').style.background = '#3e8e41';
             }
             else if(JSONobj.brd7S == 'OFF')
             {
              document.getElementById('btn7').innerHTML = JSONobj.brd7S;
              document.getElementById('btn7').style.background='#d40505';
             }

          
           document.getElementById('board7V').innerHTML = JSONobj.brd7V;
           document.getElementById('board7C').innerHTML = JSONobj.brd7C;

           if(JSONobj.brd7M=='Manuel'){
          document.getElementById("btn7").disabled = false;
          document.getElementById("brd7timerNo").disabled = true;
          document.getElementById("brd7BasS1").disabled = true;
          document.getElementById("brd7BasD1").disabled = true;
          document.getElementById("brd7SonS1").disabled = true;
          document.getElementById("brd7SonD1").disabled = true;
                
          document.getElementById('Mbtn7').innerHTML = JSONobj.brd7M;
          document.getElementById('Mbtn7').style.background = 'blue';            
           }

          if(JSONobj.brd7M=='Timer'){
            document.getElementById("btn7").disabled = true;
            document.getElementById("brd7timerNo").disabled = false;
            document.getElementById("brd7BasS1").disabled = false;
            document.getElementById("brd7BasD1").disabled = false;
            document.getElementById("brd7SonS1").disabled = false;
            document.getElementById("brd7SonD1").disabled = false;
                        
            document.getElementById('Mbtn7').innerHTML = JSONobj.brd7M;
            document.getElementById('Mbtn7').style.background = 'green';
          }
           
           if(JSONobj.brd7ConnectSt == 'Connected')
          {
            document.getElementById('brd7connectStatus').innerHTML = JSONobj.brd7ConnectSt;
            document.getElementById('brd7connectStatus').style.color = '#3e8e41';
          }

           if(JSONobj.brd7ConnectSt == 'No Connection')
          {
            document.getElementById('brd7connectStatus').innerHTML = JSONobj.brd7ConnectSt;
            document.getElementById('brd7connectStatus').style.color = '#d40505';
          }

          }


          
          //---------------Board--8-----------

          if(JSONobj.brd8V)
          {

      addData8(t, JSONobj.brd8C);

                  
            //8. BUTON
            if(JSONobj.brd8S == 'ON')
            {
              document.getElementById('btn8').innerHTML = JSONobj.brd8S;
              document.getElementById('btn8').style.background = '#3e8e41';
             }
             else if(JSONobj.brd8S == 'OFF')
             {
              document.getElementById('btn8').innerHTML = JSONobj.brd8S;
              document.getElementById('btn8').style.background='#d40505';
             }

          
           document.getElementById('board8V').innerHTML = JSONobj.brd8V;
           document.getElementById('board8C').innerHTML = JSONobj.brd8C;

           if(JSONobj.brd8M=='Manuel'){
          document.getElementById("btn8").disabled = false;
          document.getElementById("brd8timerNo").disabled = true;
          document.getElementById("brd8BasS1").disabled = true;
          document.getElementById("brd8BasD1").disabled = true;
          document.getElementById("brd8SonS1").disabled = true;
          document.getElementById("brd8SonD1").disabled = true;
                
          document.getElementById('Mbtn8').innerHTML = JSONobj.brd8M;
          document.getElementById('Mbtn8').style.background = 'blue';            
           }

          if(JSONobj.brd8M=='Timer'){
            document.getElementById("btn8").disabled = true;
            document.getElementById("brd8timerNo").disabled = false;
            document.getElementById("brd8BasS1").disabled = false;
            document.getElementById("brd8BasD1").disabled = false;
            document.getElementById("brd8SonS1").disabled = false;
            document.getElementById("brd8SonD1").disabled = false;
                        
            document.getElementById('Mbtn8').innerHTML = JSONobj.brd8M;
            document.getElementById('Mbtn8').style.background = 'green';
          }
           
           if(JSONobj.brd8ConnectSt == 'Connected')
          {
            document.getElementById('brd8connectStatus').innerHTML = JSONobj.brd8ConnectSt;
            document.getElementById('brd8connectStatus').style.color = '#3e8e41';
          }

           if(JSONobj.brd8ConnectSt == 'No Connection')
          {
            document.getElementById('brd8connectStatus').innerHTML = JSONobj.brd8ConnectSt;
            document.getElementById('brd8connectStatus').style.color = '#d40505';
          }

          }

          //---------------Board--9-----------

          if(JSONobj.brd9V)
          {

      addData9(t, JSONobj.brd9C);

                  
            //9. BUTON
            if(JSONobj.brd9S == 'ON')
            {
              document.getElementById('btn9').innerHTML = JSONobj.brd9S;
              document.getElementById('btn9').style.background = '#3e8e41';
             }
             else if(JSONobj.brd9S == 'OFF')
             {
              document.getElementById('btn9').innerHTML = JSONobj.brd9S;
              document.getElementById('btn9').style.background='#d40505';
             }

          
           document.getElementById('board9V').innerHTML = JSONobj.brd9V;
           document.getElementById('board9C').innerHTML = JSONobj.brd9C;

           if(JSONobj.brd9M=='Manuel'){
          document.getElementById("btn9").disabled = false;
          document.getElementById("brd9timerNo").disabled = true;
          document.getElementById("brd9BasS1").disabled = true;
          document.getElementById("brd9BasD1").disabled = true;
          document.getElementById("brd9SonS1").disabled = true;
          document.getElementById("brd9SonD1").disabled = true;
                
          document.getElementById('Mbtn9').innerHTML = JSONobj.brd9M;
          document.getElementById('Mbtn9').style.background = 'blue';            
           }

          if(JSONobj.brd9M=='Timer'){
            document.getElementById("btn9").disabled = true;
            document.getElementById("brd9timerNo").disabled = false;
            document.getElementById("brd9BasS1").disabled = false;
            document.getElementById("brd9BasD1").disabled = false;
            document.getElementById("brd9SonS1").disabled = false;
            document.getElementById("brd9SonD1").disabled = false;
                        
            document.getElementById('Mbtn9').innerHTML = JSONobj.brd9M;
            document.getElementById('Mbtn9').style.background = 'green';
          }
           
           if(JSONobj.brd9ConnectSt == 'Connected')
          {
            document.getElementById('brd9connectStatus').innerHTML = JSONobj.brd9ConnectSt;
            document.getElementById('brd9connectStatus').style.color = '#3e8e41';
          }

           if(JSONobj.brd9ConnectSt == 'No Connection')
          {
            document.getElementById('brd9connectStatus').innerHTML = JSONobj.brd9ConnectSt;
            document.getElementById('brd9connectStatus').style.color = '#d40505';
          }

          }

          //---------------Board--10-----------

          if(JSONobj.brd10V)
          {

      addData10(t, JSONobj.brd10C);

                  
            //10. BUTON
            if(JSONobj.brd10S == 'ON')
            {
              document.getElementById('btn10').innerHTML = JSONobj.brd10S;
              document.getElementById('btn10').style.background = '#3e8e41';
             }
             else if(JSONobj.brd10S == 'OFF')
             {
              document.getElementById('btn10').innerHTML = JSONobj.brd10S;
              document.getElementById('btn10').style.background='#d40505';
             }

          
           document.getElementById('board10V').innerHTML = JSONobj.brd10V;
           document.getElementById('board10C').innerHTML = JSONobj.brd10C;

           if(JSONobj.brd10M=='Manuel'){
          document.getElementById("btn10").disabled = false;
          document.getElementById("brd10timerNo").disabled = true;
          document.getElementById("brd10BasS1").disabled = true;
          document.getElementById("brd10BasD1").disabled = true;
          document.getElementById("brd10SonS1").disabled = true;
          document.getElementById("brd10SonD1").disabled = true;
                
          document.getElementById('Mbtn10').innerHTML = JSONobj.brd10M;
          document.getElementById('Mbtn10').style.background = 'blue';            
           }

          if(JSONobj.brd10M=='Timer'){
            document.getElementById("btn10").disabled = true;
            document.getElementById("brd10timerNo").disabled = false;
            document.getElementById("brd10BasS1").disabled = false;
            document.getElementById("brd10BasD1").disabled = false;
            document.getElementById("brd10SonS1").disabled = false;
            document.getElementById("brd10SonD1").disabled = false;
                        
            document.getElementById('Mbtn10').innerHTML = JSONobj.brd10M;
            document.getElementById('Mbtn10').style.background = 'green';
          }
           
           if(JSONobj.brd10ConnectSt == 'Connected')
          {
            document.getElementById('brd10connectStatus').innerHTML = JSONobj.brd10ConnectSt;
            document.getElementById('brd10connectStatus').style.color = '#3e8e41';
          }

           if(JSONobj.brd10ConnectSt == 'No Connection')
          {
            document.getElementById('brd10connectStatus').innerHTML = JSONobj.brd10ConnectSt;
            document.getElementById('brd10connectStatus').style.color = '#d40505';
          }

          }


            }
  }
  

  function button()
     {
        
        if(document.getElementById("btn").innerHTML == 'ON')
        {
          btn = "brd1S=OFF";
        }
        else if(document.getElementById("btn").innerHTML == 'OFF')
        {
          btn = "brd1S=ON";
        }
        websock.send(btn);
     }

  function button2()
     {
        
        if(document.getElementById("btn2").innerHTML == 'ON')
        {
          btn2 = "brd2S=OFF";
        }
        else if(document.getElementById("btn2").innerHTML == 'OFF')
        {
          btn2 = "brd2S=ON";
        }
        websock.send(btn2);
     }
      
   function button3()
     {
        
        if(document.getElementById("btn3").innerHTML == 'ON')
        {
          btn3 = "brd3S=OFF";
        }
        else if(document.getElementById("btn3").innerHTML == 'OFF')
        {
          btn3 = "brd3S=ON";
        }
        websock.send(btn3);
     } 

   function button4()
     {
        
        if(document.getElementById("btn4").innerHTML == 'ON')
        {
          btn4 = "brd4S=OFF";
        }
        else if(document.getElementById("btn4").innerHTML == 'OFF')
        {
          btn4 = "brd4S=ON";
        }
        websock.send(btn4);
     } 

   function button5()
     {
        
        if(document.getElementById("btn5").innerHTML == 'ON')
        {
          btn5 = "brd5S=OFF";
        }
        else if(document.getElementById("btn5").innerHTML == 'OFF')
        {
          btn5 = "brd5S=ON";
        }
        websock.send(btn5);
     } 

     
   function button6()
     {
        
        if(document.getElementById("btn6").innerHTML == 'ON')
        {
          btn6 = "brd6S=OFF";
        }
        else if(document.getElementById("btn6").innerHTML == 'OFF')
        {
          btn6 = "brd6S=ON";
        }
        websock.send(btn6);
     }
      
   function button7()
     {
        
        if(document.getElementById("btn7").innerHTML == 'ON')
        {
          btn7 = "brd7S=OFF";
        }
        else if(document.getElementById("btn7").innerHTML == 'OFF')
        {
          btn7 = "brd7S=ON";
        }
        websock.send(btn7);
     } 


   function button8()
     {
        
        if(document.getElementById("btn8").innerHTML == 'ON')
        {
          btn8 = "brd8S=OFF";
        }
        else if(document.getElementById("btn8").innerHTML == 'OFF')
        {
          btn8 = "brd8S=ON";
        }
        websock.send(btn8);
     } 

   function button9()
     {
        
        if(document.getElementById("btn9").innerHTML == 'ON')
        {
          btn9 = "brd9S=OFF";
        }
        else if(document.getElementById("btn9").innerHTML == 'OFF')
        {
          btn9 = "brd9S=ON";
        }
        websock.send(btn9);
     } 

   function button10()
     {
        
        if(document.getElementById("btn10").innerHTML == 'ON')
        {
          btn10 = "brd10S=OFF";
        }
        else if(document.getElementById("btn10").innerHTML == 'OFF')
        {
          btn10 = "brd10S=ON";
        }
        websock.send(btn10);
     } 

              
     
    function Mod1()
    {
      if(document.getElementById("Mbtn1").innerHTML == 'Timer')
        {
          Mbtn1 = "Mode1=Manuel";
        }
        else if(document.getElementById("Mbtn1").innerHTML == 'Manuel')
        {
          Mbtn1 = "Mode1=Timer";
        }
        websock.send(Mbtn1);
           
    }

    function Mod2()
    {
      if(document.getElementById("Mbtn2").innerHTML == 'Timer')
        {
          Mbtn2 = "Mode2=Manuel";
        }
        else if(document.getElementById("Mbtn2").innerHTML == 'Manuel')
        {
          Mbtn2 = "Mode2=Timer";
        }
        websock.send(Mbtn2);
           
    }

    function Mod3()
    {
      if(document.getElementById("Mbtn3").innerHTML == 'Timer')
        {
          Mbtn3 = "Mode3=Manuel";
        }
        else if(document.getElementById("Mbtn3").innerHTML == 'Manuel')
        {
          Mbtn3 = "Mode3=Timer";
        }
        websock.send(Mbtn3);
           
    }   

     
    function Mod4()
    {
      if(document.getElementById("Mbtn4").innerHTML == 'Timer')
        {
          Mbtn4 = "Mode4=Manuel";
        }
        else if(document.getElementById("Mbtn4").innerHTML == 'Manuel')
        {
          Mbtn4 = "Mode4=Timer";
        }
        websock.send(Mbtn4);
           
    }    
    
    function Mod5()
    {
      if(document.getElementById("Mbtn5").innerHTML == 'Timer')
        {
          Mbtn5 = "Mode5=Manuel";
        }
        else if(document.getElementById("Mbtn5").innerHTML == 'Manuel')
        {
          Mbtn5 = "Mode5=Timer";
        }
        websock.send(Mbtn5);
           
    } 
    function Mod6()
    {
      if(document.getElementById("Mbtn6").innerHTML == 'Timer')
        {
          Mbtn6 = "Mode6=Manuel";
        }
        else if(document.getElementById("Mbtn6").innerHTML == 'Manuel')
        {
          Mbtn6 = "Mode6=Timer";
        }
        websock.send(Mbtn6);
           
    }

               
    function Mod7()
    {
      if(document.getElementById("Mbtn7").innerHTML == 'Timer')
        {
          Mbtn7 = "Mode7=Manuel";
        }
        else if(document.getElementById("Mbtn7").innerHTML == 'Manuel')
        {
          Mbtn7 = "Mode7=Timer";
        }
        websock.send(Mbtn7);
           
    } 
    
    function Mod8()
    {
      if(document.getElementById("Mbtn8").innerHTML == 'Timer')
        {
          Mbtn8 = "Mode8=Manuel";
        }
        else if(document.getElementById("Mbtn8").innerHTML == 'Manuel')
        {
          Mbtn8 = "Mode8=Timer";
        }
        websock.send(Mbtn8);
           
    }

    function Mod9()
    {
      if(document.getElementById("Mbtn9").innerHTML == 'Timer')
        {
          Mbtn9 = "Mode9=Manuel";
        }
        else if(document.getElementById("Mbtn9").innerHTML == 'Manuel')
        {
          Mbtn9 = "Mode9=Timer";
        }
        websock.send(Mbtn9);
           
    }

    function Mod10()
    {
      if(document.getElementById("Mbtn10").innerHTML == 'Timer')
        {
          Mbtn10 = "Mode10=Manuel";
        }
        else if(document.getElementById("Mbtn10").innerHTML == 'Manuel')
        {
          Mbtn10 = "Mode10=Timer";
        }
        websock.send(Mbtn10);
           
    }    
        
    function sendinput()
    {
       var BasSaatdk = document.getElementById("brd1BasS1").value*60;
       var basdk = document.getElementById("brd1BasD1").value;
       var sonSaatdk = document.getElementById("brd1SonS1").value*60;
       var sondk = document.getElementById("brd1SonD1").value;
       var basTdk = parseInt(BasSaatdk) + parseInt(basdk) ;
       var sonTdk = parseInt(sonSaatdk) + parseInt(sondk) ;
       console.log(basTdk);
       console.log(sonTdk);
       if ( document.getElementById("brd1timerNo").value ==1){
        brd1time1 = "brd1time1="+"bas="+basTdk+"Son="+sonTdk;
        websock.send(brd1time1);
       }
       if ( document.getElementById("brd1timerNo").value ==2){
        brd1time2 = "brd1time2="+"bas="+basTdk+"Son="+sonTdk;
        websock.send(brd1time2);
       }       

    }
    

    function brd2time()
    {
       var BasSaatdk = document.getElementById("brd2BasS1").value*60;
       var basdk = document.getElementById("brd2BasD1").value;
       var sonSaatdk = document.getElementById("brd2SonS1").value*60;
       var sondk = document.getElementById("brd2SonD1").value;
       var basTdk = parseInt(BasSaatdk) + parseInt(basdk) ;
       var sonTdk = parseInt(sonSaatdk) + parseInt(sondk) ;
       console.log(basTdk);
       console.log(sonTdk);
       brd2time1 = "brd2time1="+"bas="+basTdk+"Son="+sonTdk;
       console.log(brd2time1);
      websock.send(brd2time1);
    }

    function brd3time()
    {
       var BasSaatdk = document.getElementById("brd3BasS1").value*60;
       var basdk = document.getElementById("brd3BasD1").value;
       var sonSaatdk = document.getElementById("brd3SonS1").value*60;
       var sondk = document.getElementById("brd3SonD1").value;
       var basTdk = parseInt(BasSaatdk) + parseInt(basdk) ;
       var sonTdk = parseInt(sonSaatdk) + parseInt(sondk) ;
       console.log(basTdk);
       console.log(sonTdk);
       if ( document.getElementById("brd3timerNo").value ==1){
        brd3time1 = "brd3time1="+"bas="+basTdk+"Son="+sonTdk;
        websock.send(brd3time1);
       }
       if ( document.getElementById("brd3timerNo").value ==2){
        brd3time2 = "brd3time2="+"bas="+basTdk+"Son="+sonTdk;
        websock.send(brd3time2);       }  
    }   

    function brd4time()
    {
       var BasSaatdk = document.getElementById("brd4BasS1").value*60;
       var basdk = document.getElementById("brd4BasD1").value;
       var sonSaatdk = document.getElementById("brd4SonS1").value*60;
       var sondk = document.getElementById("brd4SonD1").value;
       var basTdk = parseInt(BasSaatdk) + parseInt(basdk) ;
       var sonTdk = parseInt(sonSaatdk) + parseInt(sondk) ;
       console.log(basTdk);
       console.log(sonTdk);
       if ( document.getElementById("brd4timerNo").value ==1){
        brd4time1 = "brd4time1="+"bas="+basTdk+"Son="+sonTdk;
        websock.send(brd4time1);
       }
       if ( document.getElementById("brd4timerNo").value ==2){
        brd4time2 = "brd4time2="+"bas="+basTdk+"Son="+sonTdk;
        websock.send(brd4time2);       }  
    }     

    function brd5time()
    {
       var BasSaatdk = document.getElementById("brd5BasS1").value*60;
       var basdk = document.getElementById("brd5BasD1").value;
       var sonSaatdk = document.getElementById("brd5SonS1").value*60;
       var sondk = document.getElementById("brd5SonD1").value;
       var basTdk = parseInt(BasSaatdk) + parseInt(basdk) ;
       var sonTdk = parseInt(sonSaatdk) + parseInt(sondk) ;
       console.log(basTdk);
       console.log(sonTdk);
       if ( document.getElementById("brd5timerNo").value ==1){
        brd5time1 = "brd5time1="+"bas="+basTdk+"Son="+sonTdk;
        websock.send(brd5time1);
       }
       if ( document.getElementById("brd5timerNo").value ==2){
        brd5time2 = "brd5time2="+"bas="+basTdk+"Son="+sonTdk;
        websock.send(brd5time2);       }  
    }

    
    function brd6time()
    {
       var BasSaatdk = document.getElementById("brd6BasS1").value*60;
       var basdk = document.getElementById("brd6BasD1").value;
       var sonSaatdk = document.getElementById("brd6SonS1").value*60;
       var sondk = document.getElementById("brd6SonD1").value;
       var basTdk = parseInt(BasSaatdk) + parseInt(basdk) ;
       var sonTdk = parseInt(sonSaatdk) + parseInt(sondk) ;
       console.log(basTdk);
       console.log(sonTdk);
       if ( document.getElementById("brd6timerNo").value ==1){
        brd6time1 = "brd6time1="+"bas="+basTdk+"Son="+sonTdk;
        websock.send(brd6time1);
       }
       if ( document.getElementById("brd6timerNo").value ==2){
        brd6time2 = "brd6time2="+"bas="+basTdk+"Son="+sonTdk;
        websock.send(brd6time2);       }  
    }

    
    function brd7time()
    {
       var BasSaatdk = document.getElementById("brd7BasS1").value*60;
       var basdk = document.getElementById("brd7BasD1").value;
       var sonSaatdk = document.getElementById("brd7SonS1").value*60;
       var sondk = document.getElementById("brd7SonD1").value;
       var basTdk = parseInt(BasSaatdk) + parseInt(basdk) ;
       var sonTdk = parseInt(sonSaatdk) + parseInt(sondk) ;
       console.log(basTdk);
       console.log(sonTdk);
       if ( document.getElementById("brd7timerNo").value ==1){
        brd7time1 = "brd7time1="+"bas="+basTdk+"Son="+sonTdk;
        websock.send(brd7time1);
       }
       if ( document.getElementById("brd7timerNo").value ==2){
        brd7time2 = "brd7time2="+"bas="+basTdk+"Son="+sonTdk;
        websock.send(brd7time2);       }  
    }
    

    function brd8time()
    {
       var BasSaatdk = document.getElementById("brd8BasS1").value*60;
       var basdk = document.getElementById("brd8BasD1").value;
       var sonSaatdk = document.getElementById("brd8SonS1").value*60;
       var sondk = document.getElementById("brd8SonD1").value;
       var basTdk = parseInt(BasSaatdk) + parseInt(basdk) ;
       var sonTdk = parseInt(sonSaatdk) + parseInt(sondk) ;
       console.log(basTdk);
       console.log(sonTdk);
       if ( document.getElementById("brd8timerNo").value ==1){
        brd8time1 = "brd8time1="+"bas="+basTdk+"Son="+sonTdk;
        websock.send(brd8time1);
       }
       if ( document.getElementById("brd8timerNo").value ==2){
        brd8time2 = "brd8time2="+"bas="+basTdk+"Son="+sonTdk;
        websock.send(brd8time2);       }  
    }

     function brd9time()
    {
       var BasSaatdk = document.getElementById("brd9BasS1").value*60;
       var basdk = document.getElementById("brd9BasD1").value;
       var sonSaatdk = document.getElementById("brd9SonS1").value*60;
       var sondk = document.getElementById("brd9SonD1").value;
       var basTdk = parseInt(BasSaatdk) + parseInt(basdk) ;
       var sonTdk = parseInt(sonSaatdk) + parseInt(sondk) ;
       console.log(basTdk);
       console.log(sonTdk);
       if ( document.getElementById("brd9timerNo").value ==1){
        brd9time1 = "brd9time1="+"bas="+basTdk+"Son="+sonTdk;
        websock.send(brd9time1);
       }
       if ( document.getElementById("brd9timerNo").value ==2){
        brd9time2 = "brd9time2="+"bas="+basTdk+"Son="+sonTdk;
        websock.send(brd9time2);       }  
    }


     function brd10time()
    {
       var BasSaatdk = document.getElementById("brd10BasS1").value*60;
       var basdk = document.getElementById("brd10BasD1").value;
       var sonSaatdk = document.getElementById("brd10SonS1").value*60;
       var sondk = document.getElementById("brd10SonD1").value;
       var basTdk = parseInt(BasSaatdk) + parseInt(basdk) ;
       var sonTdk = parseInt(sonSaatdk) + parseInt(sondk) ;
       console.log(basTdk);
       console.log(sonTdk);
       if ( document.getElementById("brd10timerNo").value ==1){
        brd10time1 = "brd10time1="+"bas="+basTdk+"Son="+sonTdk;
        websock.send(brd10time1);
       }
       if ( document.getElementById("brd10timerNo").value ==2){
        brd10time2 = "brd10time2="+"bas="+basTdk+"Son="+sonTdk;
        websock.send(brd10time2);       }  
    }       
    
</script>
</html>
)=====";
