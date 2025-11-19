RevanScript (RVS) - Sadə və açıq mənbəli skript dilidir.
Bu lahiyə öyrənmək və təcrübə məqsədilə hazırlanmışdır.
Kod açıqdır və dəyişdirilə bilər, amma kommersiya məqsədilə paylaşmaq qadağandır.

----------------------------------

Nümunə açar sözlər (RVS)

out (output) - ekarana dəyişənin dəyərini çıxış vermək üçün dür.

inp (input) - klaviyaturadan məlumat almaq üçün əsas açar sözdür.

var (variable) - dəyişən yaratmaq və dəyər vermək üçün açar sözdür.

prt (print) - string literalı ekrana çıxarmaq üçün açar sözdür.

end - normalda proqram bitəndə terminal a pause verir ki cli ekran aktiv qalsın onu sonlandırmaq üçündür.

-----------------------------------

C faylını kompilator ilə executabe fayla çevirmək üçün GCC istifadə etmənizi töfsiyə edirəm. Xüsusi olaraq UPX proqramıda lazımdır. Compile etmək üçün daha minimal executabe (exe) faylı çıxarmaq üçün lazımdır.
Hazır executable.cmd faylı ilə çox asan bir şəkildə executable fayl yarada bilərsiniz tək kliklə mümkün.

-------------------------------------

Nümunə kodlar

 * Nümunə 1
   var text; -> text dəyişəni yaradır və NULL məlumat daxil edilir.
   inp text; -> klaviyaturadan text dəyişəninə məlumat yazırıq.
   out text; -> text dəyişənin dəyərini ekrana çap edir.

* Nümunə 2
  prt "Hello, World"; -> Ekrana Hello, World sözü çap edilir.


* Nümunə 3
   end; -> Terminalı pause rejimindən çıxarıb sonlandırır proqramı.


-------------------------------------

Müəllif : Rəvan Babayev
