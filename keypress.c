bool handleIo() {
  switch (getch()) {
    case 'Q':
      return !askYN("realy quit? [Y/N]:");
  }
  return 1;
}