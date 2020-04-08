
void *translation(SHIP *sh, int sizeVertical, int sizeHorizontal) {

  if(sh -> kind != L_GUY) {
    for(int i=0; i < sh -> columns; i++) {
      for(int j=0; j < sh -> rows; j++) {
        sh -> bp = changeCellValue(sh -> bp, i, j, '0');
        sh -> bp = changeCellValue(sh -> bp, i + sizeVertical, j + sizeVertical, '1');
        }
      }
    }
  else sh -> bp = sh -> bp;
}
