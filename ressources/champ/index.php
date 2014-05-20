<html>
	<head>
		<meta charset="utf-8"/>
		<meta name="robots" content="index, follow, all"/>
		<meta name="title" content="CHAMP Accueil"/>
		<link rel="stylesheet" href="css/main.css" />
		<title>CHAMP Accueil</title>
	</head>
	<body>
		<?php include("sections/header.php"); ?>
		<article>
			<div id="box0" class="inline">
				<h1>Welcolme</h1>
				<br />
				<p>Server path: __SERVER_PATH__</p>
				<p>To start the servers: [SERVER]/.handlers/start.sh</p>
				<p>To stop the servers: [SERVER]/.handlers/stop.sh</p>
			</div>
			<div id="box1" class="inline">
				<h1>Apache</h1>
				<br />
				<p>Version: Apache/2.2.27 (Unix)</p>
				<br />
				<p>Running on port: __APACHE_PORT__</p>
				<p>SSL port: __SSL_PORT__</p>
				<br />
				<p>Location: [SERVER]/apache2/bin/apachectl</p>
				<br />
				<p>Starter: [SERVER]/.handlers/start_apache.sh</p>
				<p>Stopper: [SERVER]/.handlers/stop_apache.sh</p>
			</div>
			<div id="box2" class="inline">
				<h1>Mysql</h1>
				<br />
				<p>Running on port: __MYSQL_PORT__</p>
				<br />
				<p>Location: [SERVER]/mysql/bin/mysql</p>
				<br />
				<p>Connections informations:</p>
				<br />
				<p>Host: Localhost</p>
				<p>Port: __MYSQL_PORT__</p>
				<p>Socket: [SERVER]/tmp/mysql.sock</p>
				<p>User: root</p>
				<p>Password: (your password)</p>
				<br />
				<p>Starter: [SERVER]/.handlers/start_mysql.sh</p>
				<p>Stopper: [SERVER]/.handlers/stop_mysql.sh</p>
			</div>
		</article>
	</body>
</html>
<style>




article
{
	width: 1000px;
	margin: auto; 
	margin-top: 50px;
}
#box0
{
width: 100%;
border: 1px #303838 solid;
margin-right:40px;
height: 130px;;
border-radius: 5px;
margin-bottom: 40px;
color: #303838;
font-family: Verdana;
}
#box1
{
width: 47.7%;
border: 1px #303838 solid;
margin-right:40px;
height: 260px;;
border-radius: 5px;
color: #303838;
font-family: Verdana;
}
#box2
{
width: 47.5%;
border: 1px #303838 solid;
border-radius: 5px;
height: 350px;;
color: #303838;
font-family: Verdana;
}
#box1 p
{
margin-left: 20px;
}
#box2 p
{
margin-left: 20px;
}
#box0 p
{
margin-left: 50px;
}
