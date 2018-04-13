<?php

session_start();
$result;
$krushkal_cost = 0;

    $krushkal_path = "";

          $krushkal_time = "";



$url=$_SERVER["PHP_SELF"];

if ($_SERVER["REQUEST_METHOD"] == "POST") {

  if (isset($_POST["Submit"])) {

      $_SESSION["no_city"] = $_POST["no_city"];

      $_SESSION["no_road"] = $_POST["no_road"];

}else

      if(isset($_POST["reset"]))

      {

          session_destroy();

          redirect('.');

      }else

      if(isset($_POST["f_path"]))

      {
        global $result;
        $out="timeout 3 ./a.out";
        $CC="timeout 3 g++ --std=c++11";
        $filename_code = "main.cpp";
        $command=$CC." -lm ".$filename_code;
        $code1 = "code_header.txt";
        $code2 = "code_footer.txt";

        $file = fopen($code1,"r");
        $code = fread($file,filesize($code1));
        fclose($file);
        $verticesCount = $_SESSION["no_city"];
        $edgesCount = $_SESSION["no_road"];
        $sr = $_POST["sr_city"];
        $dd = $_POST["d_city"];
        $cc = $_POST["r_cost"];
        $s="";
        $d="";
        $c="";
        $i=0;
        for($i;$i<$edgesCount-1;$i++)
          {
            $d .= "$sr[$i],";
            $s .= "$dd[$i],";
            $c .= "$cc[$i],";
          }
            $s .= "$sr[$i]";
            $d .= "$dd[$i]";
            $c .= "$cc[$i]";
            $code .= "int v = ".$verticesCount.";
            int e = ".$edgesCount.";
            int s[] ={".$s."};
            int d[] = {".$d."};
            int c[] = {".$c."};";

            $file = fopen($code2,"r");
            $code .= fread($file,filesize($code2));
            fclose($file);

            $file_code=fopen($filename_code,"w+");
            fwrite($file_code,$code);
            fclose($file_code);

            shell_exec($command);
            $output=shell_exec($out);
            $result = explode("}", $output);
            $result[0] *= 1000000;
            $result[3] *= 1000000;
            $result[7] *= 1000000;
            $min = $result[0];
            $result[12] = "Kruskal Algorithm";
            if($min>$result[3])
            {
              $min = $result[3];
              $result[12] = "Prims Algorithm";

            }
            if($min>$result[7])
            {
              $result[12] = "Reverse Kruskal(Delete) Algorithm";
            }



      }



}

function redirect($url) {

    ob_start();

    header('Location: '.$url);

    ob_end_flush();

    die();

}

?>


<html>

    <head>

        <title>Algo Project</title>

  <meta charset="utf-8">

  <meta name="viewport" content="width=device-width, initial-scale=1">

  <link rel="stylesheet" href="/files/bootstrap.css">

  <script src="/files/jquery.js"></script>

  <script src="/files/bootstrap.js"></script>

    </head>



    <body style="margin: 30 0 30 0; background-color: ghostwhite">

        <center><h2>Algorithm Project</h2></center>

        <center><h4>Study Of Time Complexity Of Diffrent Algorithm</h4></center>

        <br><br>

        <div class="container" align="center">

            <form method="post">

                <div class="row">

                    <div class="col-md-6">

                        No. Of Cities : &nbsp;&nbsp;&nbsp;

                        <input type="number" name="no_city" value="<?php if(isset ($_SESSION["no_city"]))echo $_SESSION["no_city"] ?>">

                    </div>

                    <div class="col-md-6">

                        No. Of Roads : &nbsp;&nbsp;&nbsp;

                        <input type="number" name="no_road" value="<?php if(isset ($_SESSION["no_road"])) echo $_SESSION["no_road"] ?>">

                    </div>

                </div>

                <br>

                <?php

                if(!isset($form_1))

                {

                    echo "<center><button type='submit' class='btn btn-Success' name='Submit'>Submit</button></center>";

                }

                else

                {

                    echo "<center><button type='submit' class='btn btn-Success' name='Submit'>Update</button></center>";

                }

                ?>

            </form>

            <br><br>



                <form method="post">

                    <div class="row">

            <?php



                        if(isset($_SESSION["no_road"]))

                            if($_SESSION["no_road"]>0)

                            {

            for($i=0;$i<$_SESSION["no_road"];$i++)

            {

                $j= $i+1;

                ?>

            <div class="col-md-4">

                <center><h4>Road : <?php echo "$j"; ?></h4></center>

                    Source City : &nbsp;&nbsp;&nbsp;

                    <input type="text" name="sr_city[]" value="<?php if(isset ($sr)) echo $sr[$i] ?>"><br><br>

                    Destination City : &nbsp;&nbsp;&nbsp;

                    <input type="text" name="d_city[]" value="<?php if(isset ($d)) echo $dd[$i] ?>"><br><br>

                    Cost : &nbsp;&nbsp;&nbsp;

                    <input type="text" name="r_cost[]" value="<?php if(isset ($c)) echo $cc[$i] ?>"><br><br>

                <br>

                </div>

                    <?php

            }

                    ?>

                        <div class="col-md-12">

                         <center><button type='submit' class='btn btn-Primary' name='f_path'>Find Shortest Path</button></center>

                        </div>

                        <?php }?>

                    </div>



            </form>

            <br>

            <br>

            <div class="alert alert-success">

                <strong>Fastest Algo For The Problem : <?php echo $result[12] ?></strong>

  </div>

            <br>

            <div class="panel panel-success">

      <div class="panel-heading">Time Complexity And Cost</div>

      <div class="panel-body">

                <div class="table-responsive">

  <table class="table">

    <thead>

      <tr>

        <th>#</th>

        <th>Algorithm</th>

        <th>Time Complexity(in microsecond)</th>

        <th>Cost</th>

      </tr>

    </thead>

      <?php if(isset ($result)) if($result != ""){ ?>

    <tbody>

      <tr>

        <td>1</td>

        <td>Kruskal</td>

        <td><?php echo $result[0]; ?></td>

        <td><?php echo $result[2]; ?></td>

      </tr>

    </tbody>
    <tbody>

      <tr>

        <td>2</td>

        <td>Prims</td>

        <td><?php echo $result[3]; ?></td>

        <td><?php echo $result[2]; ?></td>

      </tr>

    </tbody>
    <tbody>

      <tr>

        <td>3</td>

        <td>Reverse Kruskal(Delete)</td>

        <td><?php echo $result[7]; ?></td>

        <td><?php echo $result[8]; ?></td>

      </tr>

    </tbody>


      <?php } ?>

  </table>

  </div>

                </div>

    </div>

            <div class="panel panel-warning">

      <div class="panel-heading">Path Taken By Diffrent Algorithm</div>

      <div class="panel-body">

                <div class="table-responsive">

  <table class="table">

    <thead>

      <tr>

        <th>#</th>

        <th>Algorithm</th>

        <th>Path</th>

      </tr>

    </thead>

      <?php if(isset ($result))if($result != ""){ ?>

        <tbody>

          <tr>

            <td>1</td>

            <td>Kruskal</td>

            <td><?php echo $result[1]; ?></td>

          </tr>

        </tbody>
        <tbody>

          <tr>

            <td>2</td>

            <td>Prims</td>

            <td><?php echo $result[4]; ?></td>

          </tr>

        </tbody>
        <tbody>

          <tr>

            <td>3</td>

            <td>Reverse Kruskal(Delete)</td>

            <td><?php echo $result[6]; ?></td>

          </tr>

        </tbody>

      <?php } ?>

  </table>

  </div>

                </div>

    </div>

            <form method="post">

            <center><button type='submit' class='btn btn-danger' name='reset'>Reset</button></center>

            </form>

        </div>

    </body>

</html>
	?>
