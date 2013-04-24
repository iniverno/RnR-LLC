# lextab.py.  This file automatically created by PLY. Don't edit.
_lexre = '(?P<t_COMMENT>/\\*.*?\\*/)|(?P<t_LINECOMMENT>\\#.*\\n)|(?P<t_ID>(\\.|[A-Za-z0-9+/_-])+)|(?P<t_newline>\\n+)|(?P<t_STRING>".*?(?<!(?<!\\\\)\\\\)")|(?P<t_RAWSTART>\\[R)|(?P<t_LPAR>\\()|(?P<t_RPAR>\\))|(?P<t_RAWEND>])|(?P<t_RBRAC>})|(?P<t_COLON>:)|(?P<t_LBRAC>{)|(?P<t_COMMA>,)'
_lextab = [
  None,
  ('t_COMMENT','COMMENT'),
  ('t_LINECOMMENT','LINECOMMENT'),
  ('t_ID','ID'),
  None,
  ('t_newline','newline'),
  (None,'STRING'),
  (None,'RAWSTART'),
  (None,'LPAR'),
  (None,'RPAR'),
  (None,'RAWEND'),
  (None,'RBRAC'),
  (None,'COLON'),
  (None,'LBRAC'),
  (None,'COMMA'),
]
_lextokens = {'COMMENT': None, 'LPAR': None, 'LBRAC': None, 'RAWEND': None, 'TYPE': None, 'OBJECT': None, 'RPAR': None, 'COMMA': None, 'LINECOMMENT': None, 'COLON': None, 'RAWSTART': None, 'RBRAC': None, 'ID': None, 'STRING': None}
_lexignore = ' \t'
_lexerrorf = 't_error'
