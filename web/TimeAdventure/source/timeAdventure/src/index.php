<?php
    if(isset($_POST['command'],$_POST['target'])){
        $command = $_POST['command'];
        $target = $_POST['target'];
        switch($command) {
			case "backup":
				$result = shell_exec("timeout 3 zip /tmp/$target -r /var/www/html 2>&1");
                die("Executed command: zip /tmp/$target -r /var/www/html 2>&1");
                break;
		}
        die("Error");
    }
?>
<html>
<head>
    <title>Time Adventure</title>
    <meta charset="UTF-8">
    <script src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.5.1/jquery.js" integrity="sha512-WNLxfP/8cVYL9sj8Jnp6et0BkubLP31jhTG9vhL/F5uEZmg5wEzKoXp1kJslzPQWwPT1eyMiSxlKCgzHLOTOTQ==" crossorigin="anonymous"></script>
</head>
<style>
        body {
            font-family: Arial, sans-serif;
            background-color: #f0f0f0; 
            background-image: url('background.jpg'); 
            background-size: cover; 
            background-position: center; 
            padding: 20px;
            margin: 0;
        }
        h1 {
            color: #fff;
            font-size: 50px;
            text-shadow: 2px 2px 4px rgba(0, 0, 0, 0.5);
        }
        form {
            background-color: #fff;
            padding: 20px;
            border-radius: 8px;
            box-shadow: 0 2px 4px rgba(0,0,0,0.1);
            display: inline-block;
        }
        input[type="text"] {
            padding: 10px;
            border: 1px solid #ccc;
            border-radius: 4px;
            width: auto; 
            flex-grow: 1; 
        }
        button {
            background-color: #007bff;
            color: white;
            padding: 10px 15px;
            border: none;
            border-radius: 4px;
            cursor: pointer;
        }
        button:hover {
            background-color: #0056b3;
        }
        pre {
            background-color: #fff;
            padding: 20px;
            margin-top: 20px;
            border-radius: 8px;
            box-shadow: 0 2px 4px rgba(0,0,0,0.1);
        }
        .center-container {
        display: flex;
        flex-direction: column;
        align-items: center;
        justify-content: center;
        height: 100vh;
        text-align: center;
        }
        form {
            background-color: #fff;
            padding: 20px;
            border-radius: 8px;
            box-shadow: 0 2px 4px rgba(0,0,0,0.1);
            display: inline-block;
        }
        .input-container {
            display: flex;
            align-items: center;
            margin-bottom: 10px; 
        }

        .file-name-prompt {
            margin: 0 10px 0 0; 
            font-size: 16px;
            color: #333;
        }
        #loading {
        display: none; 
        position: fixed; 
        top: 0; 
        left: 0; 
        width: 100vw; 
        height: 100vh; 
        background-color: rgba(255, 255, 255, 0.7); 
        z-index: 1000; 
        justify-content: center; 
        align-items: center; 
        display: flex; 
    }
    </style>
<body>
<div class="center-container">
    <h1>Backup Your Web</h1>
    <form action="#" id="backup_tool">
        <div class="input-button-container">
            <label for="target" class="file-name-prompt">Enter file name:</label>
            <input type="text" id="target" name="target" placeholder="file_name.zip" />
            <button type="submit">Backup</button>
        </div>
        <input type="hidden" name="command" value="backup" />
    </form>
    <div id="expand-icon" style="cursor:pointer; margin-top: 20px; color: #fff; text-shadow: 2px 2px 4px rgba(0, 0, 0, 0.5); font-size: 24px;">▼ What is this Web? ▼</div>
    <div id="detail-text" style="display:none; margin-top: 10px; color: #fff; text-shadow: 2px 2px 4px rgba(0, 0, 0, 0.5); font-size: 24px;">
        This website is used to back up our entire Web project, and is accessible to all employees of the IT department.
    </div>
</div>
<!-- Admin Note: I have saved a secret credentials in a super secret text file located in the "/" folder. Please make sure to check it out. -->
<div id="loading" style="display: none;">
    <img src="loading.gif" alt="Loading..." />
</div>
<pre id="result" style="margin-top: 15px;"></pre>
</body>
<script>
    var backup_tool = document.getElementById('backup_tool');
    var result_div = document.getElementById('result');

    function logSubmit(event) {
        event.preventDefault();
        $('#loading').show(); // Show the loading spinner
        $.post('index.php', $(backup_tool).serialize(), function(data) {
            $('#loading').hide(); // Hide the loading spinner once done
            result_div.innerText = data;
        });
}
    backup_tool.addEventListener('submit', logSubmit);
</script>
<script>
    $(document).ready(function() {
        $("#expand-icon").click(function() {
            $("#detail-text").slideToggle("fast", function() {
                if ($("#detail-text").is(":visible")) {
                    $("#expand-icon").html("▲ Click to hide details ▲");
                } else {
                    $("#expand-icon").html("▼ What is this Web? ▼");
                }
            });
        });
    });
</script>
</html>
