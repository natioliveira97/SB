#include <elfio/elfio.hpp>
#include <iostream>
using namespace ELFIO;

int main( void )
{
 elfio writer;

 writer.create( ELFCLASS32, ELFDATA2LSB ); 		// Cria um arquivo no padrao 32 bits e little endian
 writer.set_os_abi( ELFOSABI_LINUX );
 writer.set_type( ET_EXEC );					// Tipo executável
 writer.set_machine( EM_386 );
 section* text_sec = writer.sections.add( ".text" ); // Indica a seção de texto
 text_sec->set_type( SHT_PROGBITS );
 text_sec->set_flags( SHF_ALLOC | SHF_EXECINSTR );
 text_sec->set_addr_align( 0x10 );

 // Código em hexadecimal da seção de texto.
 char text[] = { '\xc3',
 '\x6a', '\x61',                	
 '\x6a', '\x10',                	
 '\x29', '\xc0',                	
 '\x8a', '\x44', '\x24', '\x04',       	
 '\xa2', '\xb4', '\x90', '\x04', '\x08',       	
 '\xb8', '\x04', '\x00', '\x00', '\x00',       	
 '\xbb', '\x01', '\x00', '\x00', '\x00',       	
 '\xb9', '\xb4', '\x90', '\x04', '\x08',       	
 '\xba', '\x01', '\x00', '\x00', '\x00',       	
 '\xcd', '\x80',                	
 '\xb8', '\x01', '\x00', '\x00', '\x00',       	
 '\xbb', '\x00', '\x00', '\x00', '\x00',       	
 '\xcd', '\x80'};
 text_sec->set_data( text, sizeof( text ) );
 segment* text_seg = writer.segments.add();
 text_seg->set_type( PT_LOAD );

 text_seg->set_virtual_address( 0x08048080);	// Indica o endereço do começo da seção de texto.
 text_seg->set_physical_address( 0x08048080);
 text_seg->set_flags( PF_X | PF_R );
 text_seg->set_align( 0x1000 );

 text_seg->add_section_index( text_sec->get_index(),
 text_sec->get_addr_align() );

 section* data_sec = writer.sections.add( ".data" ); // Indica a seção de dados
 data_sec->set_type( SHT_PROGBITS );
 data_sec->set_flags( SHF_ALLOC | SHF_WRITE );
 data_sec->set_addr_align( 0x4 );

 char data[] = { '\x01'};    					// Código em hexadecimal da seção de dados
 data_sec->set_data( data, sizeof( data ) );
 segment* data_seg = writer.segments.add();
 data_seg->set_type( PT_LOAD );

 data_seg->set_virtual_address( 0x080490b4);  	// Endereço do começo da seção de dados.
 data_seg->set_physical_address( 0x080490b4);
 data_seg->set_flags( PF_W | PF_R );
 data_seg->set_align( 0x10 );
 data_seg->add_section_index( data_sec->get_index(),
 data_sec->get_addr_align() );

 // Endereço do _start
 writer.set_entry(0x08048081);
 // Nome do executável
 writer.save( "teste" );
 return 0;
}