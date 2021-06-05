<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd"> 
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="de" lang="de">
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1">
<style type="text/css">
    body {
     margin: 20px auto;
	 background-color: LightGoldenRodYellow
    }
</style>
<Center>
<font face='Arial,Helvetica'>
<font color="blue">LED Laufschrift</font> <br>
Geben sie hier den Text ein. (1 bis 80 Zeichen). 
<br>

<?php		// Swissmade by dave@waldesbuehl.com
if(isset($_POST['submit'])) {							// Is executed when clicking on Submit
	$data = ($_POST['textfeld']);
	if(strlen($data) > 0 AND strlen($data) < 81 ) {  			// Only if valid number
		$path = 'myText.txt';
		$data2 = $data . "EOT\r"; 					// Attach EOT for extraction in ESP8266
		$ret = file_put_contents($path, $data2, LOCK_EX);
		if($ret === false) {
			die('Es gab einen Fehler beim schreiben Textzeile');
		}
		else {
		}	
	}
	else {									// Too few or too many characters
		echo '<font color="red">';
		echo "Das waren ". strlen($data). " Zeichen. Bitte minimum 1 Zeichen maximum 80 Zeichen eingeben";
		echo '</font>';
	}
}	
?>

<br>
<!-- Eingabefeldt und Sende-Button -->
<form action="<?php htmlentities($_SERVER['PHP_SELF']);?>" method="post" accept-charset="ISO-8859-1">
<input type="text" size="60" name="textfeld" style="font-size:18pt">
<br>
<br>
<input type="submit" name="submit" value="Senden" style="font-size:18pt">
</form>

<?php 		// Swissmade by dave@waldesbuehl.com 
if(strlen($data) > 0 AND strlen($data) < 81 ) {					// With valid input
	echo (strlen($data) ." Zeichen wurden geschrieben <br />");
	echo ('Text: "'. utf8_encode($data) . '"');
}
?>


