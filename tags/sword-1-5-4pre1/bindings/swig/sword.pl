#!/usr/bin/perl

use sword;

print "Version (should be 1.0): " , $sword::VERSION , "\n";

print "Create SWConfig object!\n";
$config = new sword::SWConfig("test.conf");

print "Load\n";
$config->Load();

print "Set value ... ";
print $config->set("Group", "Entry", "Value");
print " finished \n";

print "Get value ... ";
print $config->get("Group", "Entry");
print " finished \n";

$config->Save();

#testing SWMgr
$localemgr = sword::LocaleMgr::systemLocaleMgr();
$localemgr->setDefaultLocaleName("de");

$mgr = new sword::SWMgr();
$module = $mgr->module("GerLut1545-temp");
print "Printing WEB Module information: \n";
print "Name:\t", $module->Name(),"\nDescription:\t", $module->Description(), "\nLang:\t", $module->Lang(), "\n";

$key = new sword::VerseKey("Matthew 3:16");
$key->setPersist(1);
$module->SetKey($key);

for ($i = 0; $i < 15; $i++) {
  print "(", $module->KeyText() ,")\t", $module->StripText(), "\n";
  $key->next();
}
$key->increment(103);
print "(", $module->KeyText() ,")\t", $module->StripText(), "\n";

#testing write interface
$key->setText("John 3:16");
#$module->SetKey($key);
$module->write("This is a test entry! This tests the write abilities of the Sword Perl classes");
print "(", $module->KeyText() ,")\t", $module->StripText(), "\n";

print "Seraching for God: ";
$list = $module->Search("Gott");
print $list->Count(), " entries found!\n";
#for ( $i = 0; $i < $list->Count(); $i++) {
#  print "(", $i, ")\t", $list->GetElement()->getText(), "\n";
#  $list->next();
#}

print "Creating new module! Writing search result...";
#sword::RawText::createModule("/usr/share/sword/modules/texts/ztext/testmodule/");
#$newmod = new sword::RawText("/usr/share/sword/modules/texts/ztext/testmodule/");

#$key->setText("Genesis 1:1");
$newkey = $key->clone();
#$newmod->SetKey($newkey);
#
#for ($i = 0; $i < $list->Count(); $i++, $list->next()) {
#	$key->setText($list->GetElement()->getText());
#	$newkey->setText($list->GetElement()->getText());	
#
#	$newmod->write( $module->StripText() );
#}

print "Now create the LD module\n";

 mkdir("ldmod");
sword::zText::createModule("ldmod/",4);

print "first step}\n";

$newmod = new sword::zText("ldmod/");

print "Created module;\n";

$newkey = $newmod->CreateKey();
$newkey->setPersist(1);
$newkey->setText(" ");
$module->SetKey($newkey);

print "Loop! \n";

for ($i = 0; $i < $list->Count(); $i++) {
	print $list->GetElement()->getText() . "\n";

        $key->setText($list->GetElement()->getText());
        $newkey->setText($list->GetElement()->getText());

	$newmod->SetKey($newkey);

        $newmod->write( $module->StripText() );
	$list->next();
}
