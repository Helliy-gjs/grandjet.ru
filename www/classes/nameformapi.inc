<?php
class NameFormApi extends Api {
public $apiName = 'nameform';

private $sw,$arr;

public function __construct() {
    parent::__construct();
    $apiName = $this->tab;
    //echo $apiName;
    //die();
	$this->db = Utils::loadbdsite($_SERVER['HTTP_HOST']);
	$this->tab = $this->requestUri[1];
	$number_value_tab = $this->db->getscountab($this->tab,'id','f');
    $this->arr = array($number_value_tab +1,12,'имя000',0,0,0,12,'описание');
	}

	function getTab(){
            return $this->tab;
        }
    public function indexAction() {
    
        if($this->tab){
            $strucs = $this->db->getAll($this->tab);
                if($strucs){
            return $this->response($strucs, 200);
            }
        }
        return $this->response('DataS not found', 404);
    }  
    
    public function viewAction(){
    //id должен быть первым параметром после /users/x
    $id = array_shift($this->requestUri);
    if($id && $this->tab){
        $struc = $this->db->getById($this->tab, $id,'codparams');
        if($struc){
            return $this->response($struc, 200);
        }
    }
    return $this->response('DataV not found', 404);
    }

    public function createAction() {
        if($this->arr){
            if($this->db->createFullCategory($this->tab, $this->arr)){
                http_response_code(201);
                return $this->response('Data saved.', 201);
            }
            //else return $this->response("Saving error", 500);
        }
        
    }

        public function updateAllAction(){
        $parse_url = parse_url($this->requestUri[0]);
       if($parse_url['path'])$id = $parse_url['path'] ;
	else 	$id =  null;
        $this->arr[0]=$id;
        if(!$id || !$this->db->getById($this->tab, $id)){
            return $this->response("rec with id=$id not found", 404);
        }
        if($this->arr){
            if($struc = $this->db->updateCategory($this->tab, $this->arr,$id)){
                return $this->response('Data updated.', 204);
            }
        }
        return $this->response("Update error", 400);
    }

    public function updateAction() {
        $parse_url = parse_url($this->requestUri[0]);
      if($parse_url['path'])$id = $parse_url['path'] ;
	else 	$id =  null;
        $this->arr[0]=$id;
        if(!$id || !$this->db->getById($this->tab, $id)){
            return $this->response("rec with id=$id not found", 404);
        }
        if($this->arr){
            if($struc = $this->db->updateCategory($this->tab, $this->arr,$id)){
                return $this->response('Data updated.', 204);
            }
        }
        return $this->response("Update error", 400);
    }

    public function deleteAction(){
    $parse_url = parse_url($this->requestUri[0]);
  if($parse_url['path'])$id = $parse_url['path'] ;
	else 	$id =  null;
    if(!$id || !$this->db->getById($this->tab, $id)){
        return $this->response("User with id=$Id not found", 404);
    }
    if($this->db->deleteById($this->tab, $id)){
        return $this->response('Data deleted.', 202);
    }
    return $this->response("Delete error", 500);
}
}
?>
