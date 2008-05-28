<?php

getpost_ifset(array('id', 'tariffname', 'startingdate', 'expirationdate', 'id_trunk', 'description', 'dnidprefix', 'calleridprefix'));

$HD_Form = new FormHandler("cc_tariffplan","Ratecard");

$HD_Form -> FG_DEBUG = 0;
$HD_Form -> FG_TABLE_DEFAULT_ORDER = " tariffname";
$HD_Form -> FG_TABLE_DEFAULT_SENS = "DESC";

// Dependent Tables
$HD_Form -> FG_FK_DELETE_ALLOWED = true;
$HD_Form -> FG_FK_DELETE_CONFIRM = true;
$HD_Form -> FG_FK_WARNONLY = false;
$HD_Form -> FG_FK_TABLENAMES = array("cc_ratecard");
$HD_Form -> FG_FK_EDITION_CLAUSE = array(" idtariffplan ");
$HD_Form -> FG_FK_DELETE_MESSAGE = gettext("You are going as well to remove all the rates attached to this ratecard! Please comfirm that you really want to remove this ratecard and those rates ? ");


$HD_Form -> AddViewElement(gettext("ID"), "id", "4%", "center", "sort");
$HD_Form -> AddViewElement(gettext("TARIFFNAME"), "tariffname", "18%", "center", "sort");
$HD_Form -> AddViewElement(gettext("START DATE"), "startingdate", "13%", "center", "sort", "16", "", "", "", "", "", "display_dateformat");
$HD_Form -> AddViewElement(gettext("EXPIRY DATE"), "expirationdate", "13%", "center", "sort", "16", "", "", "", "", "", "display_dateformat");
$HD_Form -> AddViewElement(gettext("TRUNK"), "id_trunk", "11%", "center", "sort", "15", "lie", "cc_trunk", "trunkcode", "id_trunk='%id'", "%1");
$HD_Form -> AddViewElement(gettext("MINUTES USED"), "secondusedreal", "9%", "center", "SORT", "30", "", "", "", "", "", "display_minute");
$HD_Form -> AddViewElement(gettext("DNID PREFIX"), "dnidprefix", "8%", "center", "SORT", "30");
$HD_Form -> AddViewElement(gettext("CID PREFIX"), "calleridprefix", "8%", "center", "SORT", "30");

$HD_Form -> FieldViewElement ('id, tariffname, startingdate, expirationdate, id_trunk, secondusedreal, dnidprefix, calleridprefix');

$HD_Form -> FG_ACTION_SIZE_COLUMN='12%';
$HD_Form -> CV_NO_FIELDS  = gettext("THERE IS NO")." ".strtoupper($HD_Form->FG_INSTANCE_NAME)." ".gettext("CREATED!");  
$HD_Form -> CV_DISPLAY_LINE_TITLE_ABOVE_TABLE = false;
$HD_Form -> CV_TEXT_TITLE_ABOVE_TABLE = '';
$HD_Form -> CV_DISPLAY_FILTER_ABOVE_TABLE = false;


$HD_Form -> FG_EDITION = true;
$HD_Form -> FG_DELETION = true;


$HD_Form -> AddEditElement (gettext("TARIFFNAME"),
			   "tariffname",		
			   '$value',	
			   "INPUT",	
			   "size=40 maxlength=30",
			   "3",	
			   gettext("Insert the tariff name "),
			   "" , "", "",	"", "", "", "",	"");

if ($form_action=="ask-add"){	
	$begin_date = date("Y");
	$begin_date_plus = date("Y")+25;	
	$end_date = date("-m-d H:i:s");
	$comp_date = "value='".$begin_date.$end_date."'";
	$comp_date_plus = "value='".$begin_date_plus.$end_date."'";
}

$HD_Form -> AddEditElement (gettext("START DATE"),
			   "startingdate",		
			   '$value',	
			   "INPUT",	
			   "size=40 maxlength=40  $comp_date",	
			   "10",	
			   gettext("Insert the starting date"), 
			   "" , "", "",	"", "", "", "res_display_dateformat", gettext("please respect the format YYYY-MM-DD HH:MM:SS. For instance, '2004-12-31 00:00:00'"));

$HD_Form -> AddEditElement (gettext("EXPIRY DATE"),
			   "expirationdate",		
			   '$value',	
			   "INPUT",	
			   "size=40 maxlength=40  $comp_date_plus",	
			   "10",	
			   gettext("Insert the expiration date"),
			   "" , "", "",	"", "", "", "res_display_dateformat", gettext("Format YYYY-MM-DD HH:MM:SS. For instance, '2004-12-31 00:00:00'"));

$HD_Form -> AddEditElement (gettext("TRUNK"),
			   "id_trunk",	
			   '$value',	
			   "SELECT",	
			   "", "", "",	
			   "sql",		
			   "cc_trunk",	
			   "trunkcode, id_trunk",		
			   "", "", "%1", "", "");

$HD_Form -> AddEditElement (gettext("DESCRIPTION"),
			   "description",		
			   '',	
			   "TEXTAREA",	
			   "cols=50 rows=4",	
			   "",	
			   gettext("Insert the description"),
			   "" , "", "",	"", "" , "", "", "");

if ($form_action=="ask-add"){	
	$val_dnidprefix = "value='all'";
	$val_calleridprefix = "value='all'";
}

$HD_Form -> AddEditElement (gettext("DNID PREFIX"),
			   "dnidprefix",		
			   '$value',	
			   "INPUT",	
			   "size=20 $val_dnidprefix maxlength=20",	
			   "14",	
			   gettext("Insert the dnid prefix"),
			   "" , "", "",	"", "" , "", "", gettext("Set the DNID rules to choose the ratecard 'dnidprefix', by default, matches all DNID. For instance, Set the DNIDPrefix  to 900540540 to choose this ratecard when the DNID is 900540540"));


$HD_Form -> AddEditElement (gettext("CALLERID PREFIX"),
			   "calleridprefix",		
			   '$value',	
			   "INPUT",	
			   "size=20 $val_calleridprefix maxlength=20",	
			   "14",	
			   gettext("Insert the dnid prefix"),
			   "" , "", "",	"", "" , "", "", gettext("Set the CallerID rules to choose the ratecard 'calleridprefix', by default, matches all callerID. For instance, Set the calleridprefix to 900540540 to choose this ratecard when the CallerID is 900540540."));
				

$HD_Form -> FieldEditElement ('tariffname, startingdate, expirationdate, id_trunk, description, dnidprefix, calleridprefix');


if (DB_TYPE == "postgres"){
	$HD_Form -> FG_QUERY_ADITION_HIDDEN_FIELDS = "";
	$HD_Form -> FG_QUERY_ADITION_HIDDEN_VALUE  = "";	
}else{
	$HD_Form -> FG_QUERY_ADITION_HIDDEN_FIELDS = "creationdate ";
	$HD_Form -> FG_QUERY_ADITION_HIDDEN_VALUE  = "now()";	
}




$HD_Form -> FG_INTRO_TEXT_EDITION= gettext("Modify the properties of the rate card.");
$HD_Form -> FG_INTRO_TEXT_ASK_DELETION = gettext("If you really want remove this")." ".$HD_Form->FG_INSTANCE_NAME.", ".gettext("click on the delete button.");
$HD_Form -> FG_INTRO_TEXT_ADD = gettext("you can add easily a new")." ".$HD_Form->FG_INSTANCE_NAME.".<br>".gettext("Fill the following fields and confirm by clicking on the button add.");





$HD_Form -> FG_INTRO_TEXT_ADITION = '';
$HD_Form -> FG_TEXT_ADITION_CONFIRMATION = gettext("Your new")." ". $HD_Form->FG_INSTANCE_NAME." ".gettext("has been inserted.")." <br>";


$HD_Form -> FG_BUTTON_EDITION_SRC = $HD_Form -> FG_BUTTON_ADITION_SRC  = Images_Path . "/cormfirmboton.gif";
$HD_Form -> FG_BUTTON_EDITION_BOTTOM_TEXT = $HD_Form -> FG_BUTTON_ADITION_BOTTOM_TEXT =  gettext("Setup those values to create the new")." ".$HD_Form->FG_INSTANCE_NAME;



$HD_Form -> FG_GO_LINK_AFTER_ACTION_ADD = $_SERVER['PHP_SELF']."?atmenu=document&stitle=Document&wh=AC&id=";
$HD_Form -> FG_GO_LINK_AFTER_ACTION_EDIT = $_SERVER['PHP_SELF']."?atmenu=document&stitle=Document&wh=AC&id=";
$HD_Form -> FG_GO_LINK_AFTER_ACTION_DELETE = $_SERVER['PHP_SELF']."?atmenu=document&stitle=Document&wh=AC&id=";
?>