<?php



function deleteOrphans($dir = 'Uploads'){
      $db = new PDO("sqlite:Questions.db3");

        $st = $db -> prepare('SELECT * FROM FILE');
        $st -> execute();
        $filesData = $st -> fetchAll(PDO::FETCH_ASSOC);
        $path = getcwd(). DIRECTORY_SEPARATOR. $dir;
        $items = scandir($path);
        $files = array();
        $saveFile = array();
        foreach ($items as $item){
            $item_path = $path . DIRECTORY_SEPARATOR. $item;
            if (is_file($item_path)){
                $files[] = $item;
                }
                }
         $filesDeleted = 0;      
        foreach($files as $file){
        
           for ($i= 0; $i < count($filesData); $i++){
             if ($filesData[$i]['nameOnDisk']== $file){
                $saveFile[] = $file;
                }
                }
                if (!in_array($file, $saveFile)){
                    unlink($path . DIRECTORY_SEPARATOR. $file);
                    $filesDeleted++;
                    }
                }
        return $filesDeleted;
            
    }
    
    ?>