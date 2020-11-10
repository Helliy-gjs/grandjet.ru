<?php
class allmaketsApi extends Api {
public $apiName = 'allmakets';

private $model,$arr;

public function __construct() {
    parent::__construct();
    $apiName = $this->tab;
    // echo $this->method;
    // die();
    $this->db = Utils::loadbdsite($_SERVER['HTTP_HOST']);
	$this->tab = $this->requestUri[1];
	$number_value_tab = $this->db->getscountab($this->tab,'id','f');
    if(!$this->arr)$this->arr = array($number_value_tab +1,$number_value_tab +1,'имя00'.($number_value_tab +1),0,$number_value_tab +1,0,12,'описание');
    
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
        $struc = $this->db->getById($this->tab, $id);
        if($struc){
            return $this->response($struc, 200);
        }
    }
    return $this->response('DataV not found', 404);
    }

    public function createAction() {
        if($this->arr){
            if($this->db->createFullCategory($this->tab, $this->arr)){
                return $this->response('Data saved.', 201);
            }
        }
        return $this->response("Saving error", 500);
    }

    public function updateAllAction(){
        $parse_url = parse_url($this->requestUri[0]);
        $id = $parse_url['path'] ?? null;
        $this->arr[0]=$id;
        if(!$id || !$this->db->getById($this->tab, $id)){
            return $this->response("rec with id=$id not found", 404);
        }
        if($this->arr){
            if($struc = $this->db->updateCategory($this->tab, $this->arr, 'id')){
                return $this->response('Data updated.', 204);
            }
        }
        return $this->response("Update error", 400);
    }

    public function updateAction() {
        $parse_url = parse_url($this->requestUri[0]);
        $id = $parse_url['path'] ?? null;
        $this->arr[0]=$id;
        if(!$id || !$this->db->getById($this->tab, $id)){
            return $this->response("rec with id=$id not found", 404);
        }
        if($this->arr){
            if($struc = $this->db->updateCategory($this->tab, $this->arr, 'id')){
                return $this->response('Data updated.', 204);
            }
        }
        return $this->response("Update error", 400);
    }

    public function deleteAction(){
    $parse_url = parse_url($this->requestUri[0]);
    $userId = $parse_url['path'] ?? null;
    if(!$userId || !$this->db->getById($this->tab, $userId)){
        return $this->response("User with id=$userId not found", 404);
    }
    if($this->db->deleteById($this->tab, $userId)){
        return $this->response('Data deleted.', 202);
    }
    return $this->response("Delete error", 500);
}
}    