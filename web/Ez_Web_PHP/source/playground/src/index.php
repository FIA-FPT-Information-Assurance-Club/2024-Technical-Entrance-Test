<!DOCTYPE html>

<html lang="en">

<head>
    <title>Welcome to FIA</title>
    <link rel="stylesheet" type="text/css" href="assets/style.css">
</head>

<body>
    <img id="logo" src="assets/logo_fia.png" alt="FIA Icon">
    <h1>Welcome to FIA</h1>
    <p class="p-text">⚔️⚔️⚔️⚔️⚔️ We are invincible. Try to hack us ⚔️⚔️⚔️⚔️⚔️</p>
    <p class="p-text" style="font-size: 1em;">🔐 @nquangit 🔐</p>
    <button id="cont-btn">Click here to continue!</button>
    <script src="assets/javascript.js"></script>
    <!-- 🤖🤖🤖🤖🤖🤖🤖🤖🤖🤖🤖🤖🤖🤖🤖🤖🤖🤖🤖🤖🤖🤖🤖🤖🤖 -->
    <p class="p-text" style="font-size: 0.8em;">
        <?php
        if (isset($_GET['message'])) {
            echo "⚠️ " . $_GET['message'] . " ⚠️";
        }
        ?>
    </p>
</body>

</html>