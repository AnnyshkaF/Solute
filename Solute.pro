TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    md5/md5.cpp \
    md5/md5wrapper.cpp \
    jpeglib/jaricom.c \
    jpeglib/jcapimin.c \
    jpeglib/jcapistd.c \
    jpeglib/jcarith.c \
    jpeglib/jccoefct.c \
    jpeglib/jccolor.c \
    jpeglib/jcdctmgr.c \
    jpeglib/jchuff.c \
    jpeglib/jcinit.c \
    jpeglib/jcmainct.c \
    jpeglib/jcmarker.c \
    jpeglib/jcmaster.c \
    jpeglib/jcomapi.c \
    jpeglib/jcparam.c \
    jpeglib/jcprepct.c \
    jpeglib/jcsample.c \
    jpeglib/jctrans.c \
    jpeglib/jdapimin.c \
    jpeglib/jdapistd.c \
    jpeglib/jdarith.c \
    jpeglib/jdatadst.c \
    jpeglib/jdatasrc.c \
    jpeglib/jdcoefct.c \
    jpeglib/jdcolor.c \
    jpeglib/jddctmgr.c \
    jpeglib/jdhuff.c \
    jpeglib/jdinput.c \
    jpeglib/jdmainct.c \
    jpeglib/jdmarker.c \
    jpeglib/jdmaster.c \
    jpeglib/jdmerge.c \
    jpeglib/jdpostct.c \
    jpeglib/jdsample.c \
    jpeglib/jdtrans.c \
    jpeglib/jerror.c \
    jpeglib/jfdctflt.c \
    jpeglib/jfdctfst.c \
    jpeglib/jfdctint.c \
    jpeglib/jidctflt.c \
    jpeglib/jidctfst.c \
    jpeglib/jidctint.c \
    jpeglib/jmemmgr.c \
    jpeglib/jmemnobs.c \
    jpeglib/jpeglib.c \
    jpeglib/jquant1.c \
    jpeglib/jquant2.c \
    jpeglib/jutils.c \
    stb_image_write.c \
    JpegImage.cpp \
    stegRGB.cpp \
    TextDraw/TextDraw.cpp \

   HEADERS += \
    jpeglib/jconfig.h \
    jpeglib/jdct.h \
    jpeglib/jerror.h \
    jpeglib/jinclude.h \
    jpeglib/jmemsys.h \
    jpeglib/jmorecfg.h \
    jpeglib/jpegint.h \
    jpeglib/jpeglib.h \
    jpeglib/jversion.h \
    md5/md5.h \
    md5/md5wrapper.h \
    rgb_structure.h \
    stb_image_write.h \
    stegRGB.h \
    JpegImage.h \
    boost/smart_ptr/detail/atomic_count.hpp \
    boost/smart_ptr/detail/atomic_count_gcc.hpp \
    boost/smart_ptr/detail/atomic_count_gcc_x86.hpp \
    boost/smart_ptr/detail/atomic_count_nt.hpp \
    boost/smart_ptr/detail/atomic_count_pt.hpp \
    boost/smart_ptr/detail/atomic_count_solaris.hpp \
    boost/smart_ptr/detail/atomic_count_spin.hpp \
    boost/smart_ptr/detail/atomic_count_std_atomic.hpp \
    boost/smart_ptr/detail/atomic_count_sync.hpp \
    boost/smart_ptr/detail/atomic_count_win32.hpp \
    boost/smart_ptr/detail/lightweight_mutex.hpp \
    boost/smart_ptr/detail/local_counted_base.hpp \
    boost/smart_ptr/detail/local_sp_deleter.hpp \
    boost/smart_ptr/detail/lwm_nop.hpp \
    boost/smart_ptr/detail/lwm_pthreads.hpp \
    boost/smart_ptr/detail/lwm_win32_cs.hpp \
    boost/smart_ptr/detail/operator_bool.hpp \
    boost/smart_ptr/detail/quick_allocator.hpp \
    boost/smart_ptr/detail/shared_count.hpp \
    boost/smart_ptr/detail/sp_convertible.hpp \
    boost/smart_ptr/detail/sp_counted_base.hpp \
    boost/smart_ptr/detail/sp_counted_base_acc_ia64.hpp \
    boost/smart_ptr/detail/sp_counted_base_aix.hpp \
    boost/smart_ptr/detail/sp_counted_base_clang.hpp \
    boost/smart_ptr/detail/sp_counted_base_cw_ppc.hpp \
    boost/smart_ptr/detail/sp_counted_base_cw_x86.hpp \
    boost/smart_ptr/detail/sp_counted_base_gcc_ia64.hpp \
    boost/smart_ptr/detail/sp_counted_base_gcc_mips.hpp \
    boost/smart_ptr/detail/sp_counted_base_gcc_ppc.hpp \
    boost/smart_ptr/detail/sp_counted_base_gcc_sparc.hpp \
    boost/smart_ptr/detail/sp_counted_base_gcc_x86.hpp \
    boost/smart_ptr/detail/sp_counted_base_nt.hpp \
    boost/smart_ptr/detail/sp_counted_base_pt.hpp \
    boost/smart_ptr/detail/sp_counted_base_snc_ps3.hpp \
    boost/smart_ptr/detail/sp_counted_base_solaris.hpp \
    boost/smart_ptr/detail/sp_counted_base_spin.hpp \
    boost/smart_ptr/detail/sp_counted_base_std_atomic.hpp \
    boost/smart_ptr/detail/sp_counted_base_sync.hpp \
    boost/smart_ptr/detail/sp_counted_base_vacpp_ppc.hpp \
    boost/smart_ptr/detail/sp_counted_base_w32.hpp \
    boost/smart_ptr/detail/sp_counted_impl.hpp \
    boost/smart_ptr/detail/sp_disable_deprecated.hpp \
    boost/smart_ptr/detail/sp_forward.hpp \
    boost/smart_ptr/detail/sp_has_sync.hpp \
    boost/smart_ptr/detail/sp_interlocked.hpp \
    boost/smart_ptr/detail/sp_noexcept.hpp \
    boost/smart_ptr/detail/sp_nullptr_t.hpp \
    boost/smart_ptr/detail/spinlock.hpp \
    boost/smart_ptr/detail/spinlock_gcc_arm.hpp \
    boost/smart_ptr/detail/spinlock_nt.hpp \
    boost/smart_ptr/detail/spinlock_pool.hpp \
    boost/smart_ptr/detail/spinlock_pt.hpp \
    boost/smart_ptr/detail/spinlock_std_atomic.hpp \
    boost/smart_ptr/detail/spinlock_sync.hpp \
    boost/smart_ptr/detail/spinlock_w32.hpp \
    boost/smart_ptr/detail/yield_k.hpp \
    boost/smart_ptr/allocate_local_shared_array.hpp \
    boost/smart_ptr/allocate_shared_array.hpp \
    boost/smart_ptr/atomic_shared_ptr.hpp \
    boost/smart_ptr/bad_weak_ptr.hpp \
    boost/smart_ptr/enable_shared_from_raw.hpp \
    boost/smart_ptr/enable_shared_from_this.hpp \
    boost/smart_ptr/intrusive_ptr.hpp \
    boost/smart_ptr/intrusive_ref_counter.hpp \
    boost/smart_ptr/local_shared_ptr.hpp \
    boost/smart_ptr/make_local_shared.hpp \
    boost/smart_ptr/make_local_shared_array.hpp \
    boost/smart_ptr/make_local_shared_object.hpp \
    boost/smart_ptr/make_shared.hpp \
    boost/smart_ptr/make_shared_array.hpp \
    boost/smart_ptr/make_shared_object.hpp \
    boost/smart_ptr/make_unique.hpp \
    boost/smart_ptr/owner_less.hpp \
    boost/smart_ptr/scoped_array.hpp \
    boost/smart_ptr/scoped_ptr.hpp \
    boost/smart_ptr/shared_array.hpp \
    boost/smart_ptr/shared_ptr.hpp \
    boost/smart_ptr/weak_ptr.hpp \
    boost/assert.hpp \
    boost/checked_delete.hpp \
    boost/scoped_ptr.hpp \
    boost/user_interface_config.hpp \
    boost/workaround.hpp \
    boost/config.hpp \
    boost/config/abi/borland_prefix.hpp \
    boost/config/abi/borland_suffix.hpp \
    boost/config/abi/msvc_prefix.hpp \
    boost/config/abi/msvc_suffix.hpp \
    boost/config/compiler/borland.hpp \
    boost/config/compiler/clang.hpp \
    boost/config/compiler/codegear.hpp \
    boost/config/compiler/comeau.hpp \
    boost/config/compiler/common_edg.hpp \
    boost/config/compiler/compaq_cxx.hpp \
    boost/config/compiler/cray.hpp \
    boost/config/compiler/diab.hpp \
    boost/config/compiler/digitalmars.hpp \
    boost/config/compiler/gcc.hpp \
    boost/config/compiler/gcc_xml.hpp \
    boost/config/compiler/greenhills.hpp \
    boost/config/compiler/hp_acc.hpp \
    boost/config/compiler/intel.hpp \
    boost/config/compiler/kai.hpp \
    boost/config/compiler/metrowerks.hpp \
    boost/config/compiler/mpw.hpp \
    boost/config/compiler/nvcc.hpp \
    boost/config/compiler/pathscale.hpp \
    boost/config/compiler/pgi.hpp \
    boost/config/compiler/sgi_mipspro.hpp \
    boost/config/compiler/sunpro_cc.hpp \
    boost/config/compiler/vacpp.hpp \
    boost/config/compiler/visualc.hpp \
    boost/config/compiler/xlcpp.hpp \
    boost/config/compiler/xlcpp_zos.hpp \
    boost/config/detail/posix_features.hpp \
    boost/config/detail/select_compiler_config.hpp \
    boost/config/detail/select_platform_config.hpp \
    boost/config/detail/select_stdlib_config.hpp \
    boost/config/detail/suffix.hpp \
    boost/config/no_tr1/cmath.hpp \
    boost/config/no_tr1/complex.hpp \
    boost/config/no_tr1/functional.hpp \
    boost/config/no_tr1/memory.hpp \
    boost/config/no_tr1/utility.hpp \
    boost/config/platform/aix.hpp \
    boost/config/platform/amigaos.hpp \
    boost/config/platform/beos.hpp \
    boost/config/platform/bsd.hpp \
    boost/config/platform/cloudabi.hpp \
    boost/config/platform/cray.hpp \
    boost/config/platform/cygwin.hpp \
    boost/config/platform/haiku.hpp \
    boost/config/platform/hpux.hpp \
    boost/config/platform/irix.hpp \
    boost/config/platform/linux.hpp \
    boost/config/platform/macos.hpp \
    boost/config/platform/qnxnto.hpp \
    boost/config/platform/solaris.hpp \
    boost/config/platform/symbian.hpp \
    boost/config/platform/vms.hpp \
    boost/config/platform/vxworks.hpp \
    boost/config/platform/win32.hpp \
    boost/config/platform/zos.hpp \
    boost/config/stdlib/dinkumware.hpp \
    boost/config/stdlib/libcomo.hpp \
    boost/config/stdlib/libcpp.hpp \
    boost/config/stdlib/libstdcpp3.hpp \
    boost/config/stdlib/modena.hpp \
    boost/config/stdlib/msl.hpp \
    boost/config/stdlib/roguewave.hpp \
    boost/config/stdlib/sgi.hpp \
    boost/config/stdlib/stlport.hpp \
    boost/config/stdlib/vacpp.hpp \
    boost/config/stdlib/xlcpp_zos.hpp \
    boost/config/abi_prefix.hpp \
    boost/config/abi_suffix.hpp \
    boost/config/auto_link.hpp \
    boost/config/requires_threads.hpp \
    boost/config/user.hpp \
    boost/config/warning_disable.hpp \
    boost/config/workaround.hpp \
    boost/detail/winapi/detail/deprecated_namespace.hpp \
    boost/detail/winapi/access_rights.hpp \
    boost/detail/winapi/apc.hpp \
    boost/detail/winapi/basic_types.hpp \
    boost/detail/winapi/bcrypt.hpp \
    boost/detail/winapi/character_code_conversion.hpp \
    boost/detail/winapi/condition_variable.hpp \
    boost/detail/winapi/config.hpp \
    boost/detail/winapi/critical_section.hpp \
    boost/detail/winapi/crypt.hpp \
    boost/detail/winapi/dbghelp.hpp \
    boost/detail/winapi/debugapi.hpp \
    boost/detail/winapi/directory_management.hpp \
    boost/detail/winapi/dll.hpp \
    boost/detail/winapi/environment.hpp \
    boost/detail/winapi/error_codes.hpp \
    boost/detail/winapi/error_handling.hpp \
    boost/detail/winapi/event.hpp \
    boost/detail/winapi/file_management.hpp \
    boost/detail/winapi/file_mapping.hpp \
    boost/detail/winapi/get_current_process.hpp \
    boost/detail/winapi/get_current_process_id.hpp \
    boost/detail/winapi/get_current_thread.hpp \
    boost/detail/winapi/get_current_thread_id.hpp \
    boost/detail/winapi/get_last_error.hpp \
    boost/detail/winapi/get_process_times.hpp \
    boost/detail/winapi/get_system_directory.hpp \
    boost/detail/winapi/get_thread_times.hpp \
    boost/detail/winapi/handle_info.hpp \
    boost/detail/winapi/handles.hpp \
    boost/detail/winapi/heap_memory.hpp \
    boost/detail/winapi/init_once.hpp \
    boost/detail/winapi/jobs.hpp \
    boost/detail/winapi/limits.hpp \
    boost/detail/winapi/local_memory.hpp \
    boost/detail/winapi/memory.hpp \
    boost/detail/winapi/mutex.hpp \
    boost/detail/winapi/overlapped.hpp \
    boost/detail/winapi/page_protection_flags.hpp \
    boost/detail/winapi/pipes.hpp \
    boost/detail/winapi/priority_class.hpp \
    boost/detail/winapi/process.hpp \
    boost/detail/winapi/security.hpp \
    boost/detail/winapi/semaphore.hpp \
    boost/detail/winapi/shell.hpp \
    boost/detail/winapi/show_window.hpp \
    boost/detail/winapi/srw_lock.hpp \
    boost/detail/winapi/stack_backtrace.hpp \
    boost/detail/winapi/synchronization.hpp \
    boost/detail/winapi/system.hpp \
    boost/detail/winapi/thread.hpp \
    boost/detail/winapi/thread_pool.hpp \
    boost/detail/winapi/time.hpp \
    boost/detail/winapi/timers.hpp \
    boost/detail/winapi/tls.hpp \
    boost/detail/winapi/wait.hpp \
    boost/detail/winapi/waitable_timer.hpp \
    boost/detail/algorithm.hpp \
    boost/detail/allocator_utilities.hpp \
    boost/detail/atomic_count.hpp \
    boost/detail/basic_pointerbuf.hpp \
    boost/detail/binary_search.hpp \
    boost/detail/bitmask.hpp \
    boost/detail/call_traits.hpp \
    boost/detail/catch_exceptions.hpp \
    boost/detail/compressed_pair.hpp \
    boost/detail/container_fwd.hpp \
    boost/detail/dynamic_bitset.hpp \
    boost/detail/endian.hpp \
    boost/detail/fenv.hpp \
    boost/detail/has_default_constructor.hpp \
    boost/detail/identifier.hpp \
    boost/detail/indirect_traits.hpp \
    boost/detail/interlocked.hpp \
    boost/detail/is_incrementable.hpp \
    boost/detail/is_sorted.hpp \
    boost/detail/is_xxx.hpp \
    boost/detail/iterator.hpp \
    boost/detail/lcast_precision.hpp \
    boost/detail/lightweight_main.hpp \
    boost/detail/lightweight_mutex.hpp \
    boost/detail/lightweight_test.hpp \
    boost/detail/lightweight_test_report.hpp \
    boost/detail/lightweight_thread.hpp \
    boost/detail/named_template_params.hpp \
    boost/detail/no_exceptions_support.hpp \
    boost/detail/numeric_traits.hpp \
    boost/detail/ob_compressed_pair.hpp \
    boost/detail/quick_allocator.hpp \
    boost/detail/reference_content.hpp \
    boost/detail/scoped_enum_emulation.hpp \
    boost/detail/select_type.hpp \
    boost/detail/sp_typeinfo.hpp \
    boost/detail/templated_streams.hpp \
    boost/detail/utf8_codecvt_facet.hpp \
    boost/detail/utf8_codecvt_facet.ipp \
    boost/detail/workaround.hpp \
    boost/core/addressof.hpp \
    boost/core/checked_delete.hpp \
    boost/core/demangle.hpp \
    boost/core/enable_if.hpp \
    boost/core/explicit_operator_bool.hpp \
    boost/core/ignore_unused.hpp \
    boost/core/is_same.hpp \
    boost/core/lightweight_test.hpp \
    boost/core/lightweight_test_trait.hpp \
    boost/core/no_exceptions_support.hpp \
    boost/core/noncopyable.hpp \
    boost/core/null_deleter.hpp \
    boost/core/pointer_traits.hpp \
    boost/core/ref.hpp \
    boost/core/scoped_enum.hpp \
    boost/core/swap.hpp \
    boost/core/typeinfo.hpp \
    boost/core/underlying_type.hpp \
    TextDraw/textdraw.h


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../Q/Qwt
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../Q/Qwt
else:unix: LIBS += -L$$PWD/../../../../Q/Qwt/ -lqwt

INCLUDEPATH += $$PWD/../../../../Q/Qwt
DEPENDPATH += $$PWD/../../../../Q/Qwt

FORMS +=

