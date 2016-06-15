<?php
	# Name: Patrick Trinkle
	# Email: tri1@umbc.edu
	# Course: CMSC433
	# File: index.php
	# Horoscope Thing, there aren't a lot of different phrases, but that can be changed easily.
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1//EN" "http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" >
    <head>
        <title>Chinese Horoscope</title>
        <style type="text/css">
          body { text-align: center; font-family: sans-serif; margin-left: 25%; margin-right: 25%;}
          p.error { color: red; }
          hr {color: #999999; background-color: #999999; height: 1px; border: 0; }
        </style>
    </head>
    <body>
        <h1>Chinese Horoscope</h1>
    <form action="<?php echo $_SERVER['PHP_SELF']; ?>" method="post" name="theForm">
      <p>
        <label for="name">Name:</label>
        <input type="text" name="name" id="name" value=""/>
      </p>
      <p>
        <label for="year">Birth Year:</label>
        <input type="text" name="year" id="year" value=""/>
      </p>
      <p>
        <input type="submit" value="Get Horoscope" />
      </p>
    </form> 

<?php if($_SERVER['REQUEST_METHOD'] != 'GET') { 
	$name = $_POST['name'];
	$year = $_POST['year'];

	$animals = array('Rat', 'Ox', 'Tiger', 'Rabbit', 'Dragon', 'Snake', 'Horse', 'Goat', 'Monkey', 'Rooster', 'Dog', 'Pig');
?>
	<hr>

	<?php # I'm really hating the spacing thing going on here ?>

	<?php if(!preg_match('/.+/', $name)) { ?>
		<p class="error">Invalid Name.  You must enter your name</p>
	        <script type="text/javascript">
                  <!--
                    document.getElementById("year").value = "<?php echo $year; ?>";
                  // -->
                </script>
	<?php } else { ?>

	<?php 		if($year < 1899 || $year > 2099 || !preg_match('/\d{4}/', $year)) { ?>
		<p class="error">Invalid Year.  Must be in range 1900 - 2099</p>
	<?php } 	else { 
			$index = ( $year - 1900 ) % 12;
			$format = "F j, Y";
			$animal = $animals[$index];

			$set1 = array('Avoid crosswalks.', 'Avoid your family.', 'Stay clear of construction equipment.', 'Stay inside at all costs.', 'The blur in your vision is a tumor.', 'Stay away from my car.', 'Stop reading horoscopes.', 'Watch for speeding buses.');
			$set2 = array('Stay near your closest friends.', 'Say hello to your mum.', 'Give your neighbor a hug.', 'Say hello to the meteorite falling towards you right now.', 'Oh my god, run!');
			$set3 = array('learn a new programming language.', 'learn a new language.', 'step aside.', 'fall off your bike.', 'go to the doctors to get that checked out.', 'turn and run.', 'say good bye to cheese.', 'stop eating meat.', 'be more like your brother.');
			$set1size = 8;
			$set2size = 5;
			$set3size = 9;

			$numbers;
			$today = (int) date("z");
			srand($year * $today);
			for($i = 0; $i < 6; $i++) {
				$numbers[$i] = rand(1, 100);
			}

			$indexphrase1 = rand(1,10000) % $set1size;
			$indexphrase2 = rand(1,10000) % $set2size;
			$indexphrase3 = rand(1,10000) % $set3size;

			$phrase = $set1[$indexphrase1] . " " . $set2[$indexphrase2] . " Today is a good day to " . $set3[$indexphrase3];

	?>
	<script type="text/javascript">
	   <!--	
	       document.getElementById("name").value = "<?php echo $name ?>";
	       document.getElementById("year").value = "<?php echo $year; ?>";
	   // -->
	</script>
		<h2>Horoscope for <?php echo $name ?> &mdash; <?php echo date($format); ?></h2>
		<h3> Year of the <?php echo $animal ?></h3>
		<p><?php echo $phrase ?></p>
	        <p>Your luck number for today: <?php print "$numbers[0], $numbers[1], $numbers[2], $numbers[3], $numbers[4], $numbers[5]"; ?></p>
	<?php 	} ?>
	<?php } ?>
<?php } ?>

    </body>
</html>