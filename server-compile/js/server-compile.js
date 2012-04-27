

function main() {

  function BuildDone( data ) {
    $('#make_output').append( data );
    $('#source-display').hide();
    $('#nacl-display').fadeIn();
    $('#hello_nexe').attr('src','hello.nmf');
  }

  function MakeProject( data ) {
    if ( data.Ready ) {
      $.post( '/macton-nacl/server-compile/cgi-bin/make-project.cgi', BuildDone );
    }
    $('#make_output').html( data.Message );
  }

  function CompileIt() {
    // $.post( '/macton-nacl/server-compile/cgi-bin/server-compile.cgi', { src: $('#source-code').val() }, BuildDone );
    $.post( '/macton-nacl/server-compile/save_source/save_source_x86_32.cgi', { src: $('#source-code').val() }, MakeProject, "json" );
  }

  function GetSample( data ) {
    $('#source-code').val( data );
  }

  function CompileAgain() {
    $('#nacl-display').hide();    
    $('#source-display').fadeIn();    
  }

  $.get( '/macton-nacl/server-compile/hello.orig.c', GetSample );
  $('#compile-it').click( CompileIt );
  $('#compile-again').click( CompileAgain );
}


$( main );

