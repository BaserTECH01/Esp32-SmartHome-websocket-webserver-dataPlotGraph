const char serverIndex[] PROGMEM = 
R"=====(

<style>
    .button {
      padding: 15px 25px;
      font-size: 24px;
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

    #myProgress {
  width: 100%;
  background-color: #ddd;
}

#myBar {
  width: 0%;
  height: 30px;
  background-color: #04AA6D;
  text-align: center;
  line-height: 30px;
  color: white;
}

    
</style>
<script src='https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js'></script>
<body>
<center>
<form method='POST' action='#' enctype='multipart/form-data' id='upload_form'>
   <input type='file' class="button" name='update'>
        <input type='submit' class="button" value='Update'>
    </form>


 </center>
   <div id="myProgress">
  <div id="myBar">0%</div>
</div>
 <body>
 <script>
  $('form').submit(function(e){
  e.preventDefault();
  var form = $('#upload_form')[0];
  var data = new FormData(form);
   $.ajax({
  url: '/update',
  type: 'POST',
  data: data,
  contentType: false,
  processData:false,
  xhr: function() {
  var xhr = new window.XMLHttpRequest();
  xhr.upload.addEventListener('progress', function(evt) {
  if (evt.lengthComputable) {
  var per = evt.loaded / evt.total;
  //$('#prg').html('progress: ' + Math.round(per*100) + '%');
  var persentege = Math.round(per*100)
    document.getElementById("myBar").style.width=persentege+'%';
  document.getElementById("myBar").innerHTML=persentege+'%';
  }
  }, false);
  return xhr;
  },
  success:function(d, s) {
  console.log('success!')
 },
 error: function (a, b, c) {
 }
 });
 });
 </script>
)=====";
