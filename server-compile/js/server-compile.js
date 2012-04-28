

function main() {

  var outer_layout = $('body').layout( { applyDefaultStyles: true, south__size: '25%', east__size: '25%' } );
  var source_code;

  function BuildDone( data ) {
    $('#make_output').append( data.BuildOutput );
    $('#hello-nexe').attr('src','hello.nmf?id=' + data.Id);
    outer_layout.open('east');
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
    outer_layout.close('east');
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
  outer_layout.close('east');

}


$( main );

