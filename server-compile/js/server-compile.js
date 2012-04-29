 
jQuery.fn.onCapture = function( event_name, callback ) {
  this[0].addEventListener( event_name, callback, true );
  return this;
}

function TweakFloat( name, value ) {
  var tweak = $('table#tweaks').find('.' + name);
  if ( !tweak ) {
    return;
  }
  return tweak.slider('option','value',value);
}

function TweakInt32( name, value ) {
  var tweak = $('table#tweaks').find('.' + name);
  if ( !tweak ) {
    return;
  }
  return tweak.slider('option','value',value);
}

function main() {

  var outer_layout_config = { 
    applyDefaultStyles: true,
    enableCursorHotkey: false,
    east:  { size: '40%', initClosed: true },
    north: { resizable: false, closable: false, slidable: false, spacing_open: 0, initClosed: false } 
  };
  var code_panel_layout_config = {
    applyDefaultStyles: true, 
    north: { resizable: false, closable: false, slidable: false, spacing_open: 0, initClosed: false } 
  };

  var outer_layout = $('body').layout( outer_layout_config );
  var source_code  = CodeMirror( $('#source-code-display')[0], { lineNumbers: true, mode: 'text/x-csrc' } );
  var make_output  = CodeMirror( $('#make-output')[0],         { lineNumbers: true, mode: 'text/plain'  } );
  var nexe_output  = CodeMirror( $('#nexe-output')[0],         { lineNumbers: true, mode: 'text/plain'  } );
  var tweak_code   = CodeMirror( $('#tweak-code-display')[0],  { lineNumbers: true, mode: 'text/javascript', value: "// Tweak code here\n\n\n" } );
  var tweak_output = CodeMirror( $('#tweak-output')[0],        { lineNumbers: true, mode: 'text/plain'  } );

  function NexeModuleReady() {
  }

  function AddTweakFloat( tweak_description ) {
    var tweaks = $('table#tweaks');
    var tweak_float = $('<tr></tr>').appendTo( tweaks );
    var tweak_label  = $('<td style="width: 250px">' + tweak_description.Name + '</td>').appendTo( tweak_float );
    var tweak_text_id = tweak_description.Addr + '-text';
    var tweak_edit   = $('<td></td>').appendTo( tweak_float );

    var tweak_slider_config = { 
      min:   tweak_description.Min, 
      max:   tweak_description.Max, 
      value: tweak_description.Value, 
      step:  ( tweak_description.Max - tweak_description.Min ) / 100,
      change: function( e ) {
        var target = $(e.target);
        var addr   = target.data('Addr');
        var value  = target.slider('option','value');
        $('#'+tweak_text_id).html( value.toFixed(4) );
        $('#hello-nexe')[0].postMessage('$poke_float ' + addr + ' ' + value);
      }
    };

    var tweak_slider = $('<div class="' + tweak_description.VarName + '"></div>').slider( tweak_slider_config ).appendTo( tweak_edit );
    tweak_slider.data( 'Addr', tweak_description.Addr );
    var tweak_text     = $('<td style="width: 100px" id="' + tweak_text_id + '">' + tweak_description.Value + '</td>').appendTo( tweak_float );
    var tweak_var_name = $('<td style="width: 100px">' + tweak_description.VarName + '</td>').appendTo( tweak_float );
  }

  function AddTweakInt32( tweak_description ) {
    var tweaks = $('table#tweaks');
    var tweak_int32 = $('<tr></tr>').appendTo( tweaks );
    var tweak_label  = $('<td style="width: 250px">' + tweak_description.Name + '</td>').appendTo( tweak_int32 );
    var tweak_text_id = tweak_description.Addr + '-text';
    var tweak_edit   = $('<td></td>').appendTo( tweak_int32 );

    var tweak_slider_config = { 
      min:   tweak_description.Min, 
      max:   tweak_description.Max, 
      value: tweak_description.Value, 
      step:  ( tweak_description.Max - tweak_description.Min ) / 100,
      change: function( e ) {
        var target = $(e.target);
        var addr   = target.data('Addr');
        var value  = parseInt( target.slider('option','value') );
        $('#'+tweak_text_id).html( value );
        $('#hello-nexe')[0].postMessage('$poke_int32 ' + addr + ' ' + value);
      }
    };

    var tweak_slider = $('<div class="' + tweak_description.VarName + '"></div>').slider( tweak_slider_config ).appendTo( tweak_edit );
    tweak_slider.data( 'Addr', tweak_description.Addr );
    var tweak_text = $('<td style="width: 100px" id="' + tweak_text_id + '">' + tweak_description.Value + '</td>').appendTo( tweak_int32 );
    var tweak_var_name = $('<td style="width: 100px">' + tweak_description.VarName + '</td>').appendTo( tweak_int32 );
  }
  
  function NexeLogTTY( message ) {
    if ( message.data.indexOf('$tweak_float') != -1 ) {
      AddTweakFloat( JSON.parse( message.data.split('=')[1] ) );
      return;
    }
    if ( message.data.indexOf('$tweak_int32') != -1 ) {
      AddTweakInt32( JSON.parse( message.data.split('=')[1] ) );
      return;
    }
    nexe_output.setValue( nexe_output.getValue() + message.data + ( ( message.data.indexOf('\n') == -1 ) ? '\n' : '' ) );
    nexe_output.refresh();
  }

  function BuildDone( data ) {

    make_output.setValue( make_output.getValue() + data.BuildOutput );
    make_output.refresh();
   
    $('#tweaks').html('');
    $('#hello-nexe').attr('src','hello.nmf?id=' + data.Id);
    outer_layout.open('east');
    $('#close-nexe').fadeIn();
  }
 
  function CloseNexe() {
    outer_layout.close('east');
    $('#close-nexe').fadeOut();

    $('#source-code-display').appendTo( 'div.code-panel div.edit-container' );
    $('.edit-container').show();
    $('.live-container').hide();
  }

  function MakeProject( data ) {
    if ( data.Ready ) {
      $.post( '/macton-nacl/server-compile/cgi-bin/make-project.cgi', function( build_output ) { BuildDone( { Id: data.Id, BuildOutput: build_output } ) } );
    }
    nexe_output.setValue( '' );
    tweak_output.setValue('');
    make_output.setValue( data.Message );

    $('#source-code-display').appendTo( '#source-code-container' );
    $('.edit-container').hide();
    $('.live-container').show();
    $('#output-tabs a[href="#build-output-container"]').tab('show');
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
    source_code.setValue( data );
    source_code.refresh();
  }

  $.get( '/macton-nacl/server-compile/hello.orig.c', GetSample );

  $('#compile-it').click( CompileIt );
  $('#close-nexe').click( CloseNexe );

  $('#nexe-display').onCapture( 'load',    NexeModuleReady );
  $('#nexe-display').onCapture( 'message', NexeLogTTY );

  $('#output-tabs a[href="#build-output-container"]').click(function (e) {
    e.preventDefault();
    $(this).tab('show');
    make_output.refresh();
  });

  $('#output-tabs a[href="#nexe-output-container"]').click(function (e) {
    e.preventDefault();
    $(this).tab('show');
    nexe_output.refresh();
  });

  $('#output-tabs a[href="#source-code-container"]').click(function (e) {
    e.preventDefault();
    $(this).tab('show');
  });

  $('#output-tabs a[href="#tweak-container"]').click(function (e) {
    e.preventDefault();
    $(this).tab('show');
    $('#tweak-tabs a[href="#tweak-code-container"]').tab('show');
    tweak_code.refresh();
  });

  $('#tweak-run-once').click( function(e) {
    var tweak_code_text = tweak_code.getValue();
    var time            = 0;
    var TweakCounter    = function() { return 0 };
    var writeln         = function( str ) { tweak_output.setValue( tweak_output.getValue() + str + '\n' ); };
    eval( tweak_code_text );
  });

  $('#tweak-run-30Hz').click( function(e) {
    var tweak_code_text = tweak_code.getValue();
    var writeln         = function( str ) { tweak_output.setValue( tweak_output.getValue() + str + '\n' ); };
    var tweak_counter   = 0;
    var TweakCounter    = function() { return tweak_counter };
    var id              = setInterval( function() {
      var d    = new Date;
      var time = d.getMilliseconds();
      eval( tweak_code_text );
      tweak_counter++;
    }, 33 );
    $('#tweak-run-30Hz').hide();
    $('#tweak-run-once').hide();
    $('#tweak-stop').show().click( function() {
      clearInterval( id );
      $('#tweak-stop').hide();
      $('#tweak-run-30Hz').show();
      $('#tweak-run-once').show();
    });
  });

  $('#tweak-tabs a[href="#tweak-code-container"]').click(function (e) {
    e.preventDefault();
    $(this).tab('show');
    tweak_code.refresh();
  });

  $('#tweak-tabs a[href="#tweak-output-container"]').click(function (e) {
    e.preventDefault();
    $(this).tab('show');
    tweak_output.refresh();
  });

  setTimeout( function() {  outer_layout.resizeAll(); }, 1000 );
}

$( main );
