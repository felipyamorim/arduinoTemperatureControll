<?php
   date_default_timezone_set('America/Sao_Paulo');
   

	$host = "xxxx";
	$db   = "xxxx";
	$user = "xxxx";
	$pass = "xxxx";  
	$api_key = 'xxxx';

	echo '<style>  th, td { border-bottom: 1px solid #ddd;} table {  width: 100%;} th { height: 50px;}</style>  ';
	echo '<html><title>Monitor de temperatura</title><body><h1>Monitor de temperatura</h1></br><table><tr><th>Data e hora</th><th>Temperatura</th></tr>';
	
	if(isset($_GET['api_key']) && !empty($_GET['api_key'])){			
		if( $api_key == $_GET['api_key']){			
			if(isset($_GET['temperatura']) && !empty($_GET['temperatura'])){					
					$conn = mysqli_connect($host,$user,$pass,$db);
					$insert = "INSERT INTO monitor VALUES (null,'".date('d/m/Y H:i:s', time())."', '".$_GET['temperatura']."');";
					echo $insert;
					$conn->query($insert);	
					$conn->close();
			}
		}
	} 

// conecta ao banco de dados
$conn = mysqli_connect($host,$user,$pass,$db);
$query = sprintf("SELECT data, temperatura FROM monitor order by id desc limit 0, 40");
$result = $conn->query($query);


if($result->num_rows > 0)
{	
	while($linha = $result->fetch_assoc()) {
		
		echo '<tr><td>'. $linha['data'] .'</td><td>'. $linha['temperatura'] .'</td></tr>';
	}
}
echo '</table></body></html>';
$conn->close();

?>													
