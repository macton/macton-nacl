

function main() {

  var outer_layout_config = { 
    applyDefaultStyles: true,
    enableCursorHotkey: false,
    south: { size: '30%', initClosed: true },
    east:  { size: '25%', initClosed: true },
    north: { resizable: false, closable: false, slidable: false, spacing_open: 0, initClosed: false } 
  };
  var code_panel_layout_config = {
    applyDefaultStyles: true, 
    north: { resizable: false, closable: false, slidable: false, spacing_open: 0, initClosed: false } 
  };

  var outer_layout      = $('body').layout( outer_layout_config );
  var source_code;

  function BuildDone( data ) {
    $('#make_output').append( data.BuildOutput );
    $('#hello-nexe').attr('src','hello.nmf?id=' + data.Id);
    outer_layout.open('south');
    outer_layout.open('east');
    $('#close-nexe').fadeIn();
  }
 
  function CloseNexe() {
    outer_layout.close('east');
    outer_layout.close('south');
    $('#close-nexe').fadeOut();
  }

  function MakeProject( data ) {
    if ( data.Ready ) {
      $.post( '/macton-nacl/server-compile/cgi-bin/make-project.cgi', function( build_output ) { BuildDone( { Id: data.Id, BuildOutput: build_output } ) } );
    }
    $('#make_output').html( data.Message );
  }

  function CompileIt() {
    if ( source_code ) 
    {
      var source_code_text = source_code.getValue();
      $.post( '/macton-nacl/server-compile/save_source/save_source_x86_32.cgi', { src: source_code_text }, MakeProject, "json" );
    }
    CloseNexe();
  }

  function GetSample( data ) {
    // http://codemirror.net/doc/manual.html
    source_code = CodeMirror( $('#source-code-container')[0], {
      value: data,
      mode: 'text/x-csrc',
      lineNumbers: true
    })
  }

  $.get( '/macton-nacl/server-compile/hello.orig.c', GetSample );

  $('#compile-it').click( CompileIt );
  $('#close-nexe').click( CloseNexe );

  setTimeout( function() {  outer_layout.resizeAll(); }, 1000 );
  // $('body').fadeIn();
}


$( main );

